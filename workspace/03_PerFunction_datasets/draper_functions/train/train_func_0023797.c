getFile(int index) const
    {
        if(index < 0 ||
           index >= (static_cast<int>(getImpl()->files.size())))
        {
            return "";
        }

        StringSet::const_iterator iter = getImpl()->files.begin();
        std::advance( iter, index );

        return iter->c_str();
    }
