GetCachedFileAndFormat(
            FileFormat * & format, CachedFileRcPtr & cachedFile,
            const std::string & filepath)
        {

            FileCacheResultPtr result;
            {
                AutoMutex lock(g_fileCacheLock);
                FileCacheMap::iterator iter = g_fileCache.find(filepath);
                if(iter != g_fileCache.end())
                {
                    result = iter->second;
                }
                else
                {
                    result = FileCacheResultPtr(new FileCacheResult);
                    g_fileCache[filepath] = result;
                }
            }


            AutoMutex lock(result->mutex);
            if(!result->ready)
            {
                result->ready = true;
                result->error = false;

                try
                {
                    LoadFileUncached(result->format,
                                     result->cachedFile,
                                     filepath);
                }
                catch(std::exception & e)
                {
                    result->error = true;
                    result->exceptionText = e.what();
                }
                catch(...)
                {
                    result->error = true;
                    std::ostringstream os;
                    os << "An unknown error occurred in LoadFileUncached, ";
                    os << filepath;
                    result->exceptionText = os.str();
                }
            }

            if(result->error)
            {
                throw Exception(result->exceptionText.c_str());
            }
            else
            {
                format = result->format;
                cachedFile = result->cachedFile;
            }
        }
