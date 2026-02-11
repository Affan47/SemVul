ComputeLinkDeps() const
{

  if (this->Target->GetType() == cmTarget::STATIC_LIBRARY ||
      this->Target->GetType() == cmTarget::OBJECT_LIBRARY)
    return cmNinjaDeps();

  cmComputeLinkInformation* cli =
    this->Target->GetLinkInformation(this->GetConfigName());
  if(!cli)
    return cmNinjaDeps();

  const std::vector<std::string> &deps = cli->GetDepends();
  cmNinjaDeps result(deps.size());
  std::transform(deps.begin(), deps.end(), result.begin(), MapToNinjaPath());


  if(!this->ModuleDefinitionFile.empty())
    {
    result.push_back(this->ModuleDefinitionFile);
    }

  return result;
}
