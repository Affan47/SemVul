clearAutoConstant(size_t index)
    {
        GpuLogicalIndexUse* indexUse = _getFloatConstantLogicalIndexUse(index, 0, GPV_GLOBAL);

        if (indexUse)
        {
            indexUse->variability = GPV_GLOBAL;
            size_t physicalIndex = indexUse->physicalIndex;

            for (AutoConstantList::iterator i = mAutoConstants.begin();
                 i != mAutoConstants.end(); ++i)
            {
                if (i->physicalIndex == physicalIndex)
                {
                    mAutoConstants.erase(i);
                    break;
                }
            }
        }
    }
