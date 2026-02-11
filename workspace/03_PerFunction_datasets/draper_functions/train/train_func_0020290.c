CleanCMakeFiles(const char* path)
{
  std::string glob = path;
  glob += cmake::GetCMakeFilesDirectory();
  glob += "/*.cmake";
  cmsys::Glob globIt;
  globIt.FindFiles(glob);
  std::vector<std::string> files = globIt.GetFiles();
  for(std::vector<std::string>::iterator i = files.begin();
      i != files.end(); ++i)
    {
    cmSystemTools::RemoveFile(i->c_str());
    }
}
