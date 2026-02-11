CheckImplicitDirItem(std::string const& item)
{


  if(!this->LinkTypeEnabled)
    {
    return false;
    }


  std::string dir = cmSystemTools::GetFilenamePath(item);
  if(this->ImplicitLinkDirs.find(dir) == this->ImplicitLinkDirs.end())
    {


    return false;
    }


  std::string file = cmSystemTools::GetFilenameName(item);
  if(!this->ExtractAnyLibraryName.find(file))
    {
    return false;
    }


  this->AddUserItem(file, false);


  this->OrderLinkerSearchPath->AddLinkLibrary(item);

  return true;
}
