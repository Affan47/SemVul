SetParameterValue(const std::string& name, const std::string& value)
{

  std::vector<ModuleParameterGroup>::iterator pgbeginit
    = this->ParameterGroups.begin();
  std::vector<ModuleParameterGroup>::iterator pgendit
    = this->ParameterGroups.end();
  std::vector<ModuleParameterGroup>::iterator pgit;

  for (pgit = pgbeginit; pgit != pgendit; ++pgit)
    {

    std::vector<ModuleParameter>::iterator pbeginit
      = (*pgit).GetParameters().begin();
    std::vector<ModuleParameter>::iterator pendit
      = (*pgit).GetParameters().end();
    std::vector<ModuleParameter>::iterator pit;

    for (pit = pbeginit; pit != pendit; ++pit)
      {
      if ((*pit).GetName() == name)
        {
        (*pit).SetValue(value);
        return true;
        }
      }
    }

  return false;
}
