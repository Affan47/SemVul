calculateSize(void) const
    {
        size_t memSize = 0;


        Passes::const_iterator i, iend;
        iend = mPasses.end();
        for (i = mPasses.begin(); i != iend; ++i)
        {
            memSize += (*i)->calculateSize();
        }
        return memSize;
    }
