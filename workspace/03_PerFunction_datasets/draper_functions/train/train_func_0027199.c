EnforceDirectoryLevelRules(bool endScopeNicely)
{

  while(this->PolicyStack.size() > 1)
    {
    if(endScopeNicely)
      {
      this->IssueMessage(cmake::FATAL_ERROR,
                         "cmake_policy PUSH without matching POP");
      }
    this->PopPolicy(false);
    }


  if(this->CheckCMP0000)
    {
    cmOStringStream msg;
    msg << "No cmake_minimum_required command is present.  "
        << "A line of code such as\n"
        << "  cmake_minimum_required(VERSION "
        << cmVersion::GetMajorVersion() << "."
        << cmVersion::GetMinorVersion()
        << ")\n"
        << "should be added at the top of the file.  "
        << "The version specified may be lower if you wish to "
        << "support older CMake versions for this project.  "
        << "For more information run "
        << "\"cmake --help-policy CMP0000\".";
    switch (this->GetPolicyStatus(cmPolicies::CMP0000))
      {
      case cmPolicies::WARN:


        this->IssueMessage(cmake::AUTHOR_WARNING, msg.str().c_str());
      case cmPolicies::OLD:


        break;
      case cmPolicies::REQUIRED_IF_USED:
      case cmPolicies::REQUIRED_ALWAYS:
      case cmPolicies::NEW:

        this->IssueMessage(cmake::FATAL_ERROR, msg.str().c_str());
        cmSystemTools::SetFatalErrorOccured();
        return;
      }
    }
}
