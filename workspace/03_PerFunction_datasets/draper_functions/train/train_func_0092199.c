ComputePDBOutputDir(const char* config, std::string& out)
{


  std::string targetTypeName = "PDB";
  const char* propertyName = 0;
  std::string propertyNameStr = targetTypeName;
  if(!propertyNameStr.empty())
    {
    propertyNameStr += "_OUTPUT_DIRECTORY";
    propertyName = propertyNameStr.c_str();
    }


  std::string configUpper = cmSystemTools::UpperCase(config? config : "");
  const char* configProp = 0;
  std::string configPropStr = targetTypeName;
  if(!configPropStr.empty())
    {
    configPropStr += "_OUTPUT_DIRECTORY_";
    configPropStr += configUpper;
    configProp = configPropStr.c_str();
    }


  if(const char* config_outdir = this->GetProperty(configProp))
    {

    out = config_outdir;


    config = 0;
    }
  else if(const char* outdir = this->GetProperty(propertyName))
    {

    out = outdir;
    }
  if(out.empty())
    {
    return false;
    }


  out = (cmSystemTools::CollapseFullPath
         (out.c_str(), this->Makefile->GetStartOutputDirectory()));


  if(config && *config)
    {
    this->Makefile->GetLocalGenerator()->GetGlobalGenerator()->
      AppendDirectoryForConfig("/", config, "", out);
    }
  return true;
}
