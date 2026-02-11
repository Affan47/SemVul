getModifiedTime(const String& filename)
    {


        struct stat tagStat;
        bool ret = (stat(mName.c_str(), &tagStat) == 0);

        if (ret)
        {
            return tagStat.st_mtime;
        }
        else
        {
            return 0;
        }

    }
