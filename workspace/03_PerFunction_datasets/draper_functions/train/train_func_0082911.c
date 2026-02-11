BuildCaches(OpProgress *Progress, bool WithLock)
{
   if (Cache != NULL)
      return true;

   if (_config->FindB("pkgCacheFile::Generate", true) == false)
   {
      Map = new MMap(*new FileFd(_config->FindFile("Dir::Cache::pkgcache"),
		     FileFd::ReadOnly),MMap::Public|MMap::ReadOnly);
      Cache = new pkgCache(Map);
      if (_error->PendingError() == true)
         return false;
      return true;
   }

   const bool ErrorWasEmpty = _error->empty();
   if (WithLock == true)
      if (_system->Lock() == false)
	 return false;

   if (_config->FindB("Debug::NoLocking",false) == true)
      WithLock = false;

   if (_error->PendingError() == true)
      return false;

   BuildSourceList(Progress);


   bool Res = pkgCacheGenerator::MakeStatusCache(*SrcList,Progress,&Map,!WithLock);
   if (Progress != NULL)
      Progress->Done();
   if (Res == false)
      return _error->Error(_("The package lists or status file could not be parsed or opened."));


   if (ErrorWasEmpty == true && _error->empty() == false)
      _error->Warning(_("You may want to run apt-get update to correct these problems"));

   Cache = new pkgCache(Map);
   if (_error->PendingError() == true)
      return false;
   return true;
}
