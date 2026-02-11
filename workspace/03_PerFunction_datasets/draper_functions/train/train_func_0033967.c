NeedRequiresStep(cmTarget const& target)
{
  std::set<cmStdString> languages;
  target.GetLanguages(languages);
  for(std::set<cmStdString>::const_iterator l = languages.begin();
      l != languages.end(); ++l)
    {
    std::string var = "CMAKE_NEEDS_REQUIRES_STEP_";
    var += *l;
    var += "_FLAG";
    if(target.GetMakefile()->GetDefinition(var.c_str()))
      {
      return true;
      }
    }
  return false;
}
