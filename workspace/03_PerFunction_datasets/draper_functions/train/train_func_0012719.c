AddItem(std::string const& item, cmTarget* tgt)
{

  const char* config = this->Config;
  bool impexe = (tgt && tgt->IsExecutableWithExports());
  if(impexe && !this->UseImportLibrary && !this->LoaderFlag)
    {


    return;
    }

  if(tgt && tgt->IsLinkable())
    {

    if(impexe && this->LoaderFlag)
      {


      std::string linkItem;
      linkItem = this->LoaderFlag;
      std::string exe = tgt->GetFullPath(config, this->UseImportLibrary,
                                         true);
      linkItem += exe;
      this->Items.push_back(Item(linkItem, true, tgt));
      this->Depends.push_back(exe);
      }
    else
      {

      bool implib =
        (this->UseImportLibrary &&
         (impexe || tgt->GetType() == cmTarget::SHARED_LIBRARY));


      std::string lib = tgt->GetFullPath(config, implib, true);
      this->Depends.push_back(lib);

      this->AddTargetItem(lib, tgt);
      this->AddLibraryRuntimeInfo(lib, tgt);
      }
    }
  else
    {

    if(cmSystemTools::FileIsFullPath(item.c_str()))
      {
      if(cmSystemTools::FileIsDirectory(item.c_str()))
        {

        this->AddDirectoryItem(item);
        }
      else
        {

        this->Depends.push_back(item);
        this->AddFullItem(item);
        this->AddLibraryRuntimeInfo(item);
        }
      }
    else
      {

      this->AddUserItem(item, true);
      }
    }
}
