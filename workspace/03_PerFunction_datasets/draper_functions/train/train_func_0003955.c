CalculateHashes(FetchResult &Res)
{


   FileFd::OpenMode OpenMode = FileFd::ReadOnly;
   if (_config->FindB("Acquire::GzipIndexes", false) == true)
      OpenMode = FileFd::ReadOnlyGzip;

   Hashes Hash;
   FileFd Fd(Res.Filename, OpenMode);
   Hash.AddFD(Fd);
   Res.TakeHashes(Hash);
}
