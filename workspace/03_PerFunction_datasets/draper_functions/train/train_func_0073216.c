BuildAllocationOps(OpRcPtrVec & ops,
                      const Config& ,
                      const AllocationTransform& allocationTransform,
                      TransformDirection dir)
    {
        TransformDirection combinedDir = CombineTransformDirections(dir,
                                                  allocationTransform.getDirection());

        AllocationData data;
        data.allocation = allocationTransform.getAllocation();
        data.vars.resize(allocationTransform.getNumVars());
        if(!data.vars.empty())
        {
            allocationTransform.getVars(&data.vars[0]);
        }

        CreateAllocationOps(ops, data, combinedDir);
    }
