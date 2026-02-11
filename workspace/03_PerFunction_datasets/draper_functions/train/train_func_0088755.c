FileExistsInParentDirectories(const char* fname,
  const char* directory, const char* toplevel)
{
  kwsys_stl::string file = fname;
  SystemTools::ConvertToUnixSlashes(file);
  kwsys_stl::string dir = directory;
  SystemTools::ConvertToUnixSlashes(dir);
  while ( !dir.empty() )
    {
    kwsys_stl::string path = dir + "/" + file;
    if ( SystemTools::FileExists(path.c_str()) )
      {
      return path;
      }
    if ( dir.size() < strlen(toplevel) )
      {
      break;
      }
    dir = SystemTools::GetParentDirectory(dir.c_str());
    }
  return "";
}
