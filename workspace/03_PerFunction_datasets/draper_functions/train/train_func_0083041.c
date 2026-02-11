GetPolicyDefault(cmMakefile* mf, std::string const& policy,
                                  cmPolicies::PolicyStatus* defaultSetting)
{
  std::string defaultVar = "CMAKE_POLICY_DEFAULT_" + policy;
  std::string defaultValue = mf->GetSafeDefinition(defaultVar.c_str());
  if(defaultValue == "NEW")
    {
    *defaultSetting = cmPolicies::NEW;
    }
  else if(defaultValue == "OLD")
    {
    *defaultSetting = cmPolicies::OLD;
    }
  else if(defaultValue == "")
    {
    *defaultSetting = cmPolicies::WARN;
    }
  else
    {
    cmOStringStream e;
    e << defaultVar << " has value \"" << defaultValue
      << "\" but must be \"OLD\", \"NEW\", or \"\" (empty).";
    mf->IssueMessage(cmake::FATAL_ERROR, e.str().c_str());
    return false;
    }

  return true;
}
