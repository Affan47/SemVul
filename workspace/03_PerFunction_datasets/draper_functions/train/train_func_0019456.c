GetPDBName(const char* config)
{
  std::string prefix;
  std::string base;
  std::string suffix;
  this->GetFullNameInternal(config, false, prefix, base, suffix);

  std::vector<std::string> props;
  std::string configUpper =
    cmSystemTools::UpperCase(config? config : "");
  if(!configUpper.empty())
    {

    props.push_back("PDB_NAME_" + configUpper);
    }


  props.push_back("PDB_NAME");

  for(std::vector<std::string>::const_iterator i = props.begin();
      i != props.end(); ++i)
    {
    if(const char* outName = this->GetProperty(i->c_str()))
      {
      base = outName;
      break;
      }
    }
  return prefix+base+".pdb";
}
