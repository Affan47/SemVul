CreateFramework(std::string const& targetName)
{

  this->MacContentFolders.insert("Resources");
  std::string plist = this->MacContentDirectory + "Resources/Info.plist";
  this->LocalGenerator->GenerateFrameworkInfoPList(this->Target,
                                                   targetName.c_str(),
                                                   plist.c_str());


  std::string oldName;
  std::string newName;


  std::string top = this->Target->GetDirectory(this->ConfigName);
  top += "/";
  top += this->TargetNameOut;
  top += ".framework/";


  std::string versions = top;
  versions += "Versions";
  cmSystemTools::MakeDirectory(versions.c_str());


  std::string version = versions;
  version += "/";
  version += this->FrameworkVersion;
  cmSystemTools::MakeDirectory(version.c_str());


  oldName = this->FrameworkVersion;
  newName = versions;
  newName += "/Current";
  cmSystemTools::RemoveFile(newName.c_str());
  cmSystemTools::CreateSymlink(oldName.c_str(), newName.c_str());
  this->Makefile->AddCMakeOutputFile(newName.c_str());


  oldName = "Versions/Current/";
  oldName += this->TargetNameOut;
  newName = top;
  newName += this->TargetNameOut;
  cmSystemTools::RemoveFile(newName.c_str());
  cmSystemTools::CreateSymlink(oldName.c_str(), newName.c_str());
  this->Makefile->AddCMakeOutputFile(newName.c_str());


  if(this->MacContentFolders.find("Resources") !=
     this->MacContentFolders.end())
    {
    oldName = "Versions/Current/Resources";
    newName = top;
    newName += "Resources";
    cmSystemTools::RemoveFile(newName.c_str());
    cmSystemTools::CreateSymlink(oldName.c_str(), newName.c_str());
    this->Makefile->AddCMakeOutputFile(newName.c_str());
    }


  if(this->MacContentFolders.find("Headers") !=
     this->MacContentFolders.end())
    {
    oldName = "Versions/Current/Headers";
    newName = top;
    newName += "Headers";
    cmSystemTools::RemoveFile(newName.c_str());
    cmSystemTools::CreateSymlink(oldName.c_str(), newName.c_str());
    this->Makefile->AddCMakeOutputFile(newName.c_str());
    }


  if(this->MacContentFolders.find("PrivateHeaders") !=
     this->MacContentFolders.end())
    {
    oldName = "Versions/Current/PrivateHeaders";
    newName = top;
    newName += "PrivateHeaders";
    cmSystemTools::RemoveFile(newName.c_str());
    cmSystemTools::CreateSymlink(oldName.c_str(), newName.c_str());
    this->Makefile->AddCMakeOutputFile(newName.c_str());
    }
}
