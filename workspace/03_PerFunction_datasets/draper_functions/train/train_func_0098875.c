GetFrameworkFlags()
{
 if(!this->Makefile->IsOn("APPLE"))
   {
   return std::string();
   }

 std::set<cmStdString> emitted;
#ifdef __APPLE__
  emitted.insert("/System/Library/Frameworks");
#endif
  std::vector<std::string> includes;

  const char *config = this->Makefile->GetDefinition("CMAKE_BUILD_TYPE");
  this->LocalGenerator->GetIncludeDirectories(includes,
                                              this->GeneratorTarget,
                                              "C", config);


  for(std::vector<std::string>::iterator i = includes.begin();
      i != includes.end(); ++i)
    {
    if(this->Target->NameResolvesToFramework(i->c_str()))
      {
      std::string frameworkDir = *i;
      frameworkDir += "/../";
      frameworkDir = cmSystemTools::CollapseFullPath(frameworkDir.c_str());
      emitted.insert(frameworkDir);
      }
    }

  std::string flags;
  const char* cfg = this->LocalGenerator->ConfigurationName.c_str();
  if(cmComputeLinkInformation* cli = this->Target->GetLinkInformation(cfg))
    {
    std::vector<std::string> const& frameworks = cli->GetFrameworkPaths();
    for(std::vector<std::string>::const_iterator i = frameworks.begin();
        i != frameworks.end(); ++i)
      {
      if(emitted.insert(*i).second)
        {
        flags += "-F";
        flags += this->Convert(i->c_str(),
                               cmLocalGenerator::START_OUTPUT,
                               cmLocalGenerator::SHELL, true);
        flags += " ";
        }
      }
    }
  return flags;
}
