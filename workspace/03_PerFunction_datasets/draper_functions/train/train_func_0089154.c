FileExists(std::string fname)
    {
        logdebug("%s",fname.c_str());
        if(loadFromMPQ)
            return mpq.FileExists(fname.c_str());
        else
            return GetFileSize(fname.c_str());

    }
