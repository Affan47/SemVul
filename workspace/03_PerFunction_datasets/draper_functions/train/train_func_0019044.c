FlushCache()
{
  for ( std::map<cmStdString,
    cmsys::DynamicLoader::LibraryHandle>::iterator it
    = this->CacheMap.begin();
        it != this->CacheMap.end(); it++ )
    {
    cmsys::DynamicLoader::CloseLibrary(it->second);
    }
  delete cmDynamicLoaderCache::Instance;
  cmDynamicLoaderCache::Instance = 0;
}
