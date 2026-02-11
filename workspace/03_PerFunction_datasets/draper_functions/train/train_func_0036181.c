GetVersion(pkgCacheFile &, pkgCache::VerIterator V)
{
   pkgCache::PkgIterator P = V.ParentPkg();
   if (V == P.CurrentVer())
   {
      std::string inst_str = DeNull(V.VerStr());
#if 0
      pkgDepCache *DepCache = CacheFile.GetDepCache();
      pkgDepCache::StateCache &state = (*DepCache)[P];
      if (state.Upgradable())
         return "**"+inst_str;
#endif
      return inst_str;
   }

   if(V)
      return DeNull(V.VerStr());
   return "(none)";
}
