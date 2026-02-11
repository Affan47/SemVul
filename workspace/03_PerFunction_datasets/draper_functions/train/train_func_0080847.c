CreateTar(const char* outFileName,
                              const std::vector<cmStdString>& files,
                              bool gzip, bool bzip2, bool verbose)
{
#if defined(CMAKE_BUILD_WITH_CMAKE)
  std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
  std::ofstream fout(outFileName, std::ios::out | cmsys_ios_binary);
  if(!fout)
    {
    std::string e = "Cannot open output file \"";
    e += outFileName;
    e += "\": ";
    e += cmSystemTools::GetLastSystemError();
    cmSystemTools::Error(e.c_str());
    return false;
    }
  cmArchiveWrite a(fout, (gzip? cmArchiveWrite::CompressGZip :
                          (bzip2? cmArchiveWrite::CompressBZip2 :
                           cmArchiveWrite::CompressNone)),
                           cmArchiveWrite::TypeTAR);
  a.SetVerbose(verbose);
  for(std::vector<cmStdString>::const_iterator i = files.begin();
      i != files.end(); ++i)
    {
    std::string path = *i;
    if(cmSystemTools::FileIsFullPath(path.c_str()))
      {

      path = cmSystemTools::RelativePath(cwd.c_str(), path.c_str());
      }
    if(!a.Add(path))
      {
      break;
      }
    }
  if(!a)
    {
    cmSystemTools::Error(a.GetError().c_str());
    return false;
    }
  return true;
#else
  (void)outFileName;
  (void)files;
  (void)gzip;
  (void)verbose;
  return false;
#endif
}
