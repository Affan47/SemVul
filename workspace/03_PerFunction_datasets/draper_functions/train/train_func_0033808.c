CreateModuleDocsForDir(cmsys::Directory& dir,
                         cmDocumentationSection &moduleSection)
{


  std::vector<std::string> sortedFiles;
  for(unsigned int i = 0; i < dir.GetNumberOfFiles(); ++i)
  {
    sortedFiles.push_back(dir.GetFile(i));
  }
  std::sort(sortedFiles.begin(), sortedFiles.end());

  for(std::vector<std::string>::const_iterator fname = sortedFiles.begin();
      fname!=sortedFiles.end(); ++fname)
    {
    if(fname->length() > 6)
      {
      if(fname->substr(fname->length()-6, 6) == ".cmake")
        {
        std::string moduleName = fname->substr(0, fname->length()-6);


        if (this->ModulesFound.find(moduleName) == this->ModulesFound.end())
          {
          this->ModulesFound.insert(moduleName);
          std::string path = dir.GetPath();
          path += "/";
          path += (*fname);
          this->CreateSingleModule(path.c_str(), moduleName.c_str(),
                                   moduleSection);
          }
        }
      }
    }
}
