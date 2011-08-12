/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2011, Rice University
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Rice University nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/* Author: Matt Maly */

#ifndef OMPL_CONTROL_PLANNERS_SYCLOP_SYCLOPRRT_
#define OMPL_CONTROL_PLANNERS_SYCLOP_SYCLOPRRT_

#include "ompl/control/planners/syclop/Syclop.h"
#include "ompl/control/planners/syclop/Decomposition.h"
#include "ompl/control/planners/syclop/GridDecomposition.h"

namespace ompl
{
    namespace control
    {
        /* TODO could syclopRRT inherit from both Syclop and RRT, to use some of RRT's helper and setup methods?
            I imagine SyclopRRT would override solve() to call Syclop::solve(). It would provide initializeTree() and selectAndExtend(),
            which are called by Syclop::solve(). ...for now, just rewrite some RRT code. */
        class SyclopRRT : public Syclop
        {
        public:
            SyclopRRT(const SpaceInformationPtr& si, Decomposition* d) : Syclop(si,d,"SyclopRRT")
            {
            }

            virtual ~SyclopRRT(void)
            {
                freeMemory();
            }

            virtual void setup(void);
            virtual void clear(void);
            virtual void getPlannerData(base::PlannerData& data) const;

        protected:
            virtual Syclop::Motion* initializeTree(const base::State* s);
            virtual void selectAndExtend(Region& region, std::set<Motion*>& newMotions);
            void freeMemory(void);

            base::StateSamplerPtr sampler_;
            ControlSamplerPtr controlSampler_;
            std::vector<Motion*> motions_;
        };
    }
}
#endif
