CreateGlobalTarget(
  const char* name, const char* message,
  const cmCustomCommandLines* commandLines,
  std::vector<std::string> depends,
  const char* workingDirectory,
  bool depends_on_all )
{

  cmTarget target;
  target.GetProperties().SetCMakeInstance(this->CMakeInstance);
  target.SetType(cmTarget::GLOBAL_TARGET, name);
  target.SetProperty("EXCLUDE_FROM_ALL","TRUE");

  std::vector<std::string> no_outputs;
  std::vector<std::string> no_depends;

  cmCustomCommand cc(no_outputs, no_depends, *commandLines, 0,
                     workingDirectory);
  target.GetPostBuildCommands().push_back(cc);
  target.SetProperty("EchoString", message);
  if ( depends_on_all )
    {
    target.AddUtility("all");
    }
  std::vector<std::string>::iterator dit;
  for ( dit = depends.begin(); dit != depends.end(); ++ dit )
    {
    target.AddUtility(dit->c_str());
    }
  return target;
}
