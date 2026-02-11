ParseProvides(pkgCache::VerIterator &Ver)
{
   const char *Start;
   const char *Stop;
   if (Section.Find("Provides",Start,Stop) == true)
   {
      string Package;
      string Version;
      string const Arch = Ver.Arch();
      unsigned int Op;

      while (1)
      {
	 Start = ParseDepends(Start,Stop,Package,Version,Op);
	 if (Start == 0)
	    return _error->Error("Problem parsing Provides line");
	 if (Op != pkgCache::Dep::NoOp) {
	    _error->Warning("Ignoring Provides line with DepCompareOp for package %s", Package.c_str());
	 } else if ((Ver->MultiArch & pkgCache::Version::Foreign) == pkgCache::Version::Foreign) {
	    if (NewProvidesAllArch(Ver, Package, Version) == false)
	       return false;
	 } else {
	    if (NewProvides(Ver, Package, Arch, Version) == false)
	       return false;
	 }

	 if (Start == Stop)
	    break;
      }
   }

   if ((Ver->MultiArch & pkgCache::Version::Allowed) == pkgCache::Version::Allowed)
   {
      string const Package = string(Ver.ParentPkg().Name()).append(":").append("any");
      return NewProvidesAllArch(Ver, Package, Ver.VerStr());
   }
   else if ((Ver->MultiArch & pkgCache::Version::Foreign) == pkgCache::Version::Foreign)
      return NewProvidesAllArch(Ver, Ver.ParentPkg().Name(), Ver.VerStr());

   return true;
}
