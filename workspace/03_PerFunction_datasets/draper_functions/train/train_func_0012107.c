OptimizeRedundant()
    {


        if(!GetArgCount())
        {
            if(GetOp() == cAdd || GetOp() == cMin || GetOp() == cMax)
                ReplaceWithConst(0);
            else if(GetOp() == cMul)
                ReplaceWithConst(1);
            return;
        }


        if(GetArgCount() == 1)
        {
            if(GetOp() == cMul || GetOp() == cAdd || GetOp() == cMin || GetOp() == cMax)
                if(!getp0().getsign())
                    ReplaceWith(*getp0());
        }

        OptimizeDoubleNegations();
    }
