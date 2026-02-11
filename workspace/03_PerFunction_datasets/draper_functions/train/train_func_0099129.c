AppendTargetDepends(std::vector<std::string>& depends)
{

  if(this->Target->GetType() == cmTarget::STATIC_LIBRARY)
    {
    return;
    }


  const char* cfg = this->LocalGenerator->ConfigurationName.c_str();
  if(cmComputeLinkInformation* cli = this->Target->GetLinkInformation(cfg))
    {
    std::vector<std::string> const& libDeps = cli->GetDepends();
    for(std::vector<std::string>::const_iterator j = libDeps.begin();
        j != libDeps.end(); ++j)
      {
      depends.push_back(*j);
      }
    }
}
