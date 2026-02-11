FileExistsInParentDirectories(const char* fname,
  const char* directory, const char* toplevel)
{
  std::string file = fname;
  cmSystemTools::ConvertToUnixSlashes(file);
  std::string dir = directory;
  cmSystemTools::ConvertToUnixSlashes(dir);
  std::string prevDir;
  while(dir != prevDir)
    {
    std::string path = dir + "/" + file;
    if ( cmSystemTools::FileExists(path.c_str()) )
      {
      return path;
      }
    if ( dir.size() < strlen(toplevel) )
      {
      break;
      }
    prevDir = dir;
    dir = cmSystemTools::GetParentDirectory(dir.c_str());
    }
  return "";
}
