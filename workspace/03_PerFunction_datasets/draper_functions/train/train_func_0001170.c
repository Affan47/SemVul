AddInstallNamePatchRule(std::ostream& os, Indent const& indent,
                          const char* config, std::string const& toDestDirPath)
{
  if(this->ImportLibrary ||
     !(this->Target->GetType() == cmTarget::SHARED_LIBRARY ||
       this->Target->GetType() == cmTarget::MODULE_LIBRARY ||
       this->Target->GetType() == cmTarget::EXECUTABLE))
    {
    return;
    }


  std::string installNameTool =
    this->Target->GetMakefile()->GetSafeDefinition("CMAKE_INSTALL_NAME_TOOL");

  if(!installNameTool.size())
    {
    return;
    }


  std::map<cmStdString, cmStdString> install_name_remap;
  if(cmComputeLinkInformation* cli = this->Target->GetLinkInformation(config))
    {
    std::set<cmTarget*> const& sharedLibs = cli->GetSharedLibrariesLinked();
    for(std::set<cmTarget*>::const_iterator j = sharedLibs.begin();
        j != sharedLibs.end(); ++j)
      {
      cmTarget* tgt = *j;


      if(tgt->IsImported())
        {
        continue;
        }


      std::string for_build = tgt->GetInstallNameDirForBuildTree(config);
      std::string for_install = tgt->GetInstallNameDirForInstallTree(config);
      if(for_build != for_install)
        {


        std::string fname =
          this->GetInstallFilename(tgt, config, NameSO);


        for_build += fname;


        for_install += fname;


        install_name_remap[for_build] = for_install;
        }
      }
    }


  std::string new_id;
  if(this->Target->GetType() == cmTarget::SHARED_LIBRARY)
    {
    std::string for_build =
      this->Target->GetInstallNameDirForBuildTree(config);
    std::string for_install =
      this->Target->GetInstallNameDirForInstallTree(config);

    if(this->Target->IsFrameworkOnApple() && for_install.empty())
      {


      }


    if(for_build != for_install)
      {

      new_id = for_install;
      new_id += this->GetInstallFilename(this->Target, config, NameSO);
      }
    }


  if(!new_id.empty() || !install_name_remap.empty())
    {
    os << indent << "EXECUTE_PROCESS(COMMAND \"" << installNameTool;
    os << "\"";
    if(!new_id.empty())
      {
      os << "\n" << indent << "  -id \"" << new_id << "\"";
      }
    for(std::map<cmStdString, cmStdString>::const_iterator
          i = install_name_remap.begin();
        i != install_name_remap.end(); ++i)
      {
      os << "\n" << indent << "  -change \""
         << i->first << "\" \"" << i->second << "\"";
      }
    os << "\n" << indent << "  \"" << toDestDirPath << "\")\n";
    }
}
