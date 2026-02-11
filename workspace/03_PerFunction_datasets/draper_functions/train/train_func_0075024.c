AppendProperty(const char* prop, const char* value)
{
  if (!prop)
    {
    return;
    }


  std::string propname = prop;
  if ( propname == "INCLUDE_DIRECTORIES" )
    {
    std::vector<std::string> varArgsExpanded;
    cmSystemTools::ExpandListArgument(value, varArgsExpanded);
    for(std::vector<std::string>::const_iterator vi = varArgsExpanded.begin();
        vi != varArgsExpanded.end(); ++vi)
      {
      this->AddIncludeDirectory(vi->c_str());
      }
    return;
    }

  if ( propname == "LINK_DIRECTORIES" )
    {
    std::vector<std::string> varArgsExpanded;
    cmSystemTools::ExpandListArgument(value, varArgsExpanded);
    for(std::vector<std::string>::const_iterator vi = varArgsExpanded.begin();
        vi != varArgsExpanded.end(); ++vi)
      {
      this->AddLinkDirectory(vi->c_str());
      }
    return;
    }

  this->Properties.AppendProperty(prop,value,cmProperty::DIRECTORY);
}
