ComputeHash(const std::string & filename)
        {
            struct stat results;
            if (stat(filename.c_str(), &results) == 0)
            {

                std::ostringstream fasthash;
                fasthash << results.st_ino << ":";
                fasthash << results.st_mtime;
                return fasthash.str();
            }

            return "";
        }
