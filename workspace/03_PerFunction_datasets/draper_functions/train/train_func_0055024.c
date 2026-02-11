WriteStaticLibraryRules()
{
  const char* linkLanguage =
    this->Target->GetLinkerLanguage(this->GlobalGenerator);
  std::string linkRuleVar = "CMAKE_";
  if (linkLanguage)
    {
    linkRuleVar += linkLanguage;
    }
  linkRuleVar += "_CREATE_STATIC_LIBRARY";

  std::string extraFlags;
  this->LocalGenerator->AppendFlags
    (extraFlags,this->Target->GetProperty("STATIC_LIBRARY_FLAGS"));
  this->WriteLibraryRules(linkRuleVar.c_str(), extraFlags.c_str(), false);
}
