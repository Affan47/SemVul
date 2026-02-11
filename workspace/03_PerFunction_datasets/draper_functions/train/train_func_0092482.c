SetImportLinkProperty(std::string const& suffix,
                        cmTarget* target,
                        const char* propName,
                        std::vector<std::string> const& libs,
                        ImportPropertyMap& properties,
                        std::vector<std::string>& missingTargets
                       )
{

  if(libs.empty())
    {
    return;
    }


  std::string link_libs;
  const char* sep = "";
  for(std::vector<std::string>::const_iterator li = libs.begin();
      li != libs.end(); ++li)
    {

    link_libs += sep;
    sep = ";";

    std::string temp = *li;
    this->AddTargetNamespace(temp, target, missingTargets);
    link_libs += temp;
    }


  std::string prop = propName;
  prop += suffix;
  properties[prop] = link_libs;
}
