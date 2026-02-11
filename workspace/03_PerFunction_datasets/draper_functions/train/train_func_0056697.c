WriteDirectoryRule2(std::ostream& ruleFileStream,
                      cmLocalUnixMakefileGenerator3* lg,
                      const char* pass, bool check_all,
                      bool check_relink)
{

  std::string makeTarget = lg->GetMakefile()->GetStartOutputDirectory();
  makeTarget += "/";
  makeTarget += pass;


  std::vector<std::string> depends;
  for(cmTargets::iterator l = lg->GetMakefile()->GetTargets().begin();
      l != lg->GetMakefile()->GetTargets().end(); ++l)
    {
    if((l->second.GetType() == cmTarget::EXECUTABLE) ||
       (l->second.GetType() == cmTarget::STATIC_LIBRARY) ||
       (l->second.GetType() == cmTarget::SHARED_LIBRARY) ||
       (l->second.GetType() == cmTarget::MODULE_LIBRARY) ||
       (l->second.GetType() == cmTarget::UTILITY))
      {

      if((!check_all || !l->second.GetPropertyAsBool("EXCLUDE_FROM_ALL")) &&
         (!check_relink ||
          l->second.NeedRelinkBeforeInstall(lg->ConfigurationName.c_str())))
        {
        std::string tname = lg->GetRelativeTargetDirectory(l->second);
        tname += "/";
        tname += pass;
        depends.push_back(tname);
        }
      }
    }


  for(std::vector<cmLocalGenerator*>::iterator sdi =
        lg->GetChildren().begin(); sdi != lg->GetChildren().end(); ++sdi)
    {
    cmLocalUnixMakefileGenerator3* slg =
      static_cast<cmLocalUnixMakefileGenerator3*>(*sdi);
    std::string subdir = slg->GetMakefile()->GetStartOutputDirectory();
    subdir += "/";
    subdir += pass;
    depends.push_back(subdir);
    }


  if(depends.empty() && this->EmptyRuleHackDepends != "")
    {
    depends.push_back(this->EmptyRuleHackDepends);
    }


  std::string doc = "Convenience name for \"";
  doc += pass;
  doc += "\" pass in the directory.";
  std::vector<std::string> no_commands;
  lg->WriteMakeRule(ruleFileStream, doc.c_str(),
                    makeTarget.c_str(), depends, no_commands, true);
}
