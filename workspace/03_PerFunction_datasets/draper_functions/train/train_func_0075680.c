calculateSize(void) const
    {
        size_t memSize = 0;

        memSize += HighLevelGpuProgram::calculateSize();


        for (StringVector::const_iterator i = mDelegateNames.begin(); i != mDelegateNames.end(); ++i)
            memSize += (*i).size() * sizeof(char);

        return memSize;
    }
