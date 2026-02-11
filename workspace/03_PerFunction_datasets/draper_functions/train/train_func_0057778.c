AddLibraryRuntimeInfo(std::string const& fullPath,
                                                cmTarget* target)
{


  if(this->Makefile->IsOn("CMAKE_PLATFORM_HAS_INSTALLNAME"))
    {
    if(!target->HasMacOSXRpath(this->Config))
      {
      return;
      }
    }


  if(target->GetType() == cmTarget::UNKNOWN_LIBRARY)
    {
    this->AddLibraryRuntimeInfo(fullPath);
    return;
    }


  if(target->GetType() != cmTarget::SHARED_LIBRARY)
    {
    return;
    }


  std::string soName = target->GetSOName(this->Config);
  const char* soname = soName.empty()? 0 : soName.c_str();


  this->OrderRuntimeSearchPath->AddRuntimeLibrary(fullPath, soname);
  if(this->LinkWithRuntimePath)
    {
    this->OrderLinkerSearchPath->AddRuntimeLibrary(fullPath, soname);
    }
}
