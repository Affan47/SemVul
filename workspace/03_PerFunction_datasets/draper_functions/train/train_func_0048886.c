GenerateImportConfig(std::ostream& os,
                                    const char* config,
                                    std::vector<std::string> &missingTargets)
{

  std::string suffix = "_";
  if(config && *config)
    {
    suffix += cmSystemTools::UpperCase(config);
    }
  else
    {
    suffix += "NOCONFIG";
    }


  this->GenerateImportTargetsConfig(os, config, suffix, missingTargets);
}
