ParseDefineFlag(std::string const& def, bool remove)
{

  static cmsys::RegularExpression
    valid("^[-/]D[A-Za-z_][A-Za-z0-9_]*(=.*)?$");


  if(!valid.find(def.c_str()))
    {
    return false;
    }


  if((strcmp(this->LocalGenerator->GetGlobalGenerator()->GetName(),
             "Visual Studio 6") == 0) &&
     (def.find("=") != def.npos))
    {
    return false;
    }


  static cmsys::RegularExpression
    trivial("^[-/]D[A-Za-z_][A-Za-z0-9_]*(=[A-Za-z0-9_.]+)?$");
  if(!trivial.find(def.c_str()))
    {

    switch(this->GetPolicyStatus(cmPolicies::CMP0005))
      {
      case cmPolicies::WARN:
        this->IssueMessage(
          cmake::AUTHOR_WARNING,
          this->GetPolicies()->GetPolicyWarning(cmPolicies::CMP0005)
          );
      case cmPolicies::OLD:


        return false;
      case cmPolicies::REQUIRED_IF_USED:
      case cmPolicies::REQUIRED_ALWAYS:
        this->IssueMessage(
          cmake::FATAL_ERROR,
          this->GetPolicies()->GetRequiredPolicyError(cmPolicies::CMP0005)
          );
        return false;
      case cmPolicies::NEW:


        break;
      }
    }


  const char* define = def.c_str() + 2;

  if(remove)
    {
    if(const char* cdefs = this->GetProperty("COMPILE_DEFINITIONS"))
      {

      std::vector<std::string> defs;
      cmSystemTools::ExpandListArgument(cdefs, defs);


      std::string ndefs;
      const char* sep = "";
      for(std::vector<std::string>::const_iterator di = defs.begin();
          di != defs.end(); ++di)
        {
        if(*di != define)
          {
          ndefs += sep;
          sep = ";";
          ndefs += *di;
          }
        }


      this->SetProperty("COMPILE_DEFINITIONS", ndefs.c_str());
      }
    }
  else
    {

    this->AppendProperty("COMPILE_DEFINITIONS", define);
    }

  return true;
}
