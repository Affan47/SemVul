MakeDirectory(const std::string& path)
{
  if (SystemTools::FileExists(path)) {
    return SystemTools::FileIsDirectory(path);
  }
  if (path.empty()) {
    return false;
  }
  std::string dir = path;
  SystemTools::ConvertToUnixSlashes(dir);

  std::string::size_type pos = 0;
  std::string topdir;
  while ((pos = dir.find('/', pos)) != std::string::npos) {
    topdir = dir.substr(0, pos);
    Mkdir(topdir);
    pos++;
  }
  topdir = dir;
  if (Mkdir(topdir) != 0) {


    if ((errno != EEXIST)
#ifdef __BORLANDC__
        && (errno != EACCES)
#endif
          ) {
      return false;
    }
  }
  return true;
}
