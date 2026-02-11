Merge(pkgCacheGenerator &Gen,OpProgress *Prog) const
{
   string PackageFile = IndexFile("Packages");
   FileFd Pkg(PackageFile,FileFd::ReadOnly, FileFd::Extension);
   debListParser Parser(&Pkg, Architecture);

   if (_error->PendingError() == true)
      return _error->Error("Problem opening %s",PackageFile.c_str());
   if (Prog != NULL)
      Prog->SubProgress(0,Info("Packages"));
   ::URI Tmp(URI);
   if (Gen.SelectFile(PackageFile,Tmp.Host,*this) == false)
      return _error->Error("Problem with SelectFile %s",PackageFile.c_str());


   pkgCache::PkgFileIterator File = Gen.GetCurFile();
   pkgCacheGenerator::Dynamic<pkgCache::PkgFileIterator> DynFile(File);
   File->Size = Pkg.FileSize();
   File->mtime = Pkg.ModificationTime();

   if (Gen.MergeList(Parser) == false)
      return _error->Error("Problem with MergeList %s",PackageFile.c_str());


   string ReleaseFile = debReleaseIndex(URI,Dist).MetaIndexFile("InRelease");
   bool releaseExists = false;
   if (FileExists(ReleaseFile) == true)
      releaseExists = true;
   else
      ReleaseFile = debReleaseIndex(URI,Dist).MetaIndexFile("Release");

   if (releaseExists == true || FileExists(ReleaseFile) == true)
   {
      FileFd Rel;


      if (OpenMaybeClearSignedFile(ReleaseFile, Rel) == false)
	 return false;

      if (_error->PendingError() == true)
	 return false;
      Parser.LoadReleaseInfo(File,Rel,Section);
   }

   return true;
}
