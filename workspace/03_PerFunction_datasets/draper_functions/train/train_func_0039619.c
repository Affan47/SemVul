setRole(const char * role, const char * colorSpaceName)
    {

        if(colorSpaceName)
        {
            getImpl()->roles_[pystring::lower(role)] = std::string(colorSpaceName);
        }

        else
        {
            StringMap::iterator iter = getImpl()->roles_.find(pystring::lower(role));
            if(iter != getImpl()->roles_.end())
            {
                getImpl()->roles_.erase(iter);
            }
        }

        AutoMutex lock(getImpl()->cacheidMutex_);
        getImpl()->resetCacheIDs();
    }
