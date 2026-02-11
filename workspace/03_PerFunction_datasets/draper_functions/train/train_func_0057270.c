AddDependencies(cmDependInformation* info)
{
  if(this != info)
    {
    this->DependencySet.insert(info);
    }
}
