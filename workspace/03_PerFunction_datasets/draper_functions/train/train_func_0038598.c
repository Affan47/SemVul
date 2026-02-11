AppendRuleDepends(std::vector<std::string>& depends,
                    std::vector<std::string> const& ruleFiles)
{


  if(!this->Makefile->IsOn("CMAKE_SKIP_RULE_DEPENDENCY"))
    {
    depends.insert(depends.end(), ruleFiles.begin(), ruleFiles.end());
    }
}
