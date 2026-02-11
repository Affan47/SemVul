ReadPropertyEntry(std::string const& entryKey,
                                       CacheEntry& e)
{

  if(e.Type != cmCacheManager::INTERNAL)
    {
    return false;
    }

  const char* end = entryKey.c_str() + entryKey.size();
  for(const char** p = this->PersistentProperties; *p; ++p)
    {
    std::string::size_type plen = strlen(*p) + 1;
    if(entryKey.size() > plen && *(end-plen) == '-' &&
       strcmp(end-plen+1, *p) == 0)
      {
      std::string key = entryKey.substr(0, entryKey.size() - plen);
      cmCacheManager::CacheIterator it = this->GetCacheIterator(key.c_str());
      if(it.IsAtEnd())
        {

        CacheEntry& ne = this->Cache[key];
        ne.Properties.SetCMakeInstance(this->CMakeInstance);
        ne.Type = cmCacheManager::UNINITIALIZED;
        ne.SetProperty(*p, e.Value.c_str());
        }
      else
        {

        it.SetProperty(*p, e.Value.c_str());
        }
      return true;
      }
    }
  return false;
}
