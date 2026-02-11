GenerateImportFileConfig(const char* config,
                                    std::vector<std::string> &missingTargets)
{

  if(!this->IEGen->InstallsForConfig(config))
    {
    return true;
    }


  std::string fileName = this->FileDir;
  fileName += "/";
  fileName += this->FileBase;
  fileName += "-";
  if(config && *config)
    {
    fileName += cmSystemTools::LowerCase(config);
    }
  else
    {
    fileName += "noconfig";
    }
  fileName += this->FileExt;


  cmGeneratedFileStream exportFileStream(fileName.c_str(), true);
  if(!exportFileStream)
    {
    std::string se = cmSystemTools::GetLastSystemError();
    cmOStringStream e;
    e << "cannot write to file \"" << fileName.c_str()
      << "\": " << se;
    cmSystemTools::Error(e.str().c_str());
    return false;
    }
  std::ostream& os = exportFileStream;


  this->GenerateImportHeaderCode(os, config);


  this->GenerateImportConfig(os, config, missingTargets);


  this->GenerateImportFooterCode(os);


  this->ConfigImportFiles[config] = fileName;

  return true;
}
