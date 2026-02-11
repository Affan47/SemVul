GetOutputName(const char* config, bool implib)
{
  std::vector<std::string> props;
  std::string type = this->GetOutputTargetType(implib);
  std::string configUpper = cmSystemTools::UpperCase(config? config : "");
  if(!type.empty() && !configUpper.empty())
    {

    props.push_back(type + "_OUTPUT_NAME_" + configUpper);
    }
  if(!type.empty())
    {

    props.push_back(type + "_OUTPUT_NAME");
    }
  if(!configUpper.empty())
    {

    props.push_back("OUTPUT_NAME_" + configUpper);

    props.push_back(configUpper + "_OUTPUT_NAME");
    }

  props.push_back("OUTPUT_NAME");

  for(std::vector<std::string>::const_iterator i = props.begin();
      i != props.end(); ++i)
    {
    if(const char* outName = this->GetProperty(i->c_str()))
      {
      return outName;
      }
    }
  return this->GetName();
}
