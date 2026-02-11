MakeLauncher(const cmCustomCommand& cc,
                                            cmTarget* target,
                                            RelativeRoot relative)
{

  const char* prop = "RULE_LAUNCH_CUSTOM";
  const char* val = this->GetRuleLauncher(target, prop);
  if(!(val && *val))
    {
    return "";
    }


  RuleVariables vars;
  vars.RuleLauncher = prop;
  vars.CMTarget = target;
  std::string output;
  const std::vector<std::string>& outputs = cc.GetOutputs();
  if(!outputs.empty())
    {
    output = this->Convert(outputs[0].c_str(), relative, SHELL);
    }
  vars.Output = output.c_str();

  std::string launcher;
  this->ExpandRuleVariables(launcher, vars);
  if(!launcher.empty())
    {
    launcher += " ";
    }
  return launcher;
}
