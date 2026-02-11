setWorkingDir(const char * dirname)
    {
        AutoMutex lock(getImpl()->resultsCacheMutex_);

        getImpl()->workingDir_ = dirname;
        getImpl()->resultsCache_.clear();
        getImpl()->cacheID_ = "";
    }
