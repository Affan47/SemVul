UsePackage(pkgCache::PkgIterator &Pkg,
			       pkgCache::VerIterator &Ver)
{
   if (Pkg->Section == 0)
      Pkg->Section = UniqFindTagWrite("Section");

   string const static myArch = _config->Find("APT::Architecture");


   string const static essential = _config->Find("pkgCacheGen::Essential", "all");
   if (essential == "all" ||
       (essential == "native" && Pkg->Arch != 0 && myArch == Pkg.Arch()))
      if (Section.FindFlag("Essential",Pkg->Flags,pkgCache::Flag::Essential) == false)
	 return false;
   if (Section.FindFlag("Important",Pkg->Flags,pkgCache::Flag::Important) == false)
      return false;

   if (strcmp(Pkg.Name(),"apt") == 0)
   {
      if ((essential == "native" && Pkg->Arch != 0 && myArch == Pkg.Arch()) ||
	  essential == "all")
	 Pkg->Flags |= pkgCache::Flag::Essential | pkgCache::Flag::Important;
      else
	 Pkg->Flags |= pkgCache::Flag::Important;
   }

   if (ParseStatus(Pkg,Ver) == false)
      return false;
   return true;
}
