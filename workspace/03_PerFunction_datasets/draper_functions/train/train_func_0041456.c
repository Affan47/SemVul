GetGpuAllocation(AllocationData & allocation,
                              const OpRcPtr & op)
        {
            AllocationNoOpRcPtr allocationNoOpRcPtr =
                DynamicPtrCast<AllocationNoOp>(op);

            if(!allocationNoOpRcPtr)
            {
                return false;
            }

            allocationNoOpRcPtr->getGpuAllocation(allocation);
            return true;
        }
