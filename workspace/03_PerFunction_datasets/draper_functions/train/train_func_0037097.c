getCacheID() const
    {
        AutoMutex lock(getImpl()->cacheIDMutex_);

        if(getImpl()->cacheID_.empty())
        {
            std::ostringstream os;
            os << GpuLanguageToString(getImpl()->language_) << " ";
            os << getImpl()->functionName_ << " ";
            os << getImpl()->lut3DEdgeLen_;
            getImpl()->cacheID_ = os.str();
        }

        return getImpl()->cacheID_.c_str();
    }
