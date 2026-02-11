SetProperty(const char* prop, const char* value)
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
    this->SetIncludeDirectories(varArgsExpanded);
    return;
    }

  if ( propname == "LINK_DIRECTORIES" )
    {
    std::vector<std::string> varArgsExpanded;
    cmSystemTools::ExpandListArgument(value, varArgsExpanded);
    this->SetLinkDirectories(varArgsExpanded);
    return;
    }

  if ( propname == "INCLUDE_REGULAR_EXPRESSION" )
    {
    this->SetIncludeRegularExpression(value);
    return;
    }

  if ( propname == "ADDITIONAL_MAKE_CLEAN_FILES" )
    {

    if ( strcmp(this->GetCurrentDirectory(),
                this->GetStartDirectory()) != 0 )
      {
      return;
      }
    }

  this->Properties.SetProperty(prop,value,cmProperty::DIRECTORY);
}
