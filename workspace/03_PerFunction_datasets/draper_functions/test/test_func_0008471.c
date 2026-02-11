EnableLanguage(std::vector<std::string>const& languages,
                 cmMakefile *mf,
                 bool optional)
{
  this->cmGlobalGenerator::EnableLanguage(languages, mf, optional);
  std::string path;
  for(std::vector<std::string>::const_iterator l = languages.begin();
      l != languages.end(); ++l)
    {
    if(*l == "NONE")
      {
      continue;
      }
    const char* lang = l->c_str();
    std::string langComp = "CMAKE_";
    langComp += lang;
    langComp += "_COMPILER";

    if(!mf->GetDefinition(langComp.c_str()))
      {
      if(!optional)
        {
        cmSystemTools::Error(langComp.c_str(),
                             " not set, after EnableLanguage");
        }
      continue;
      }
    const char* name = mf->GetRequiredDefinition(langComp.c_str());
    if(!cmSystemTools::FileIsFullPath(name))
      {
      path = cmSystemTools::FindProgram(name);
      }
    else
      {
      path = name;
      }
    if((path.size() == 0 || !cmSystemTools::FileExists(path.c_str()))
        && (optional==false))
      {
      std::string message = "your ";
      message += lang;
      message += " compiler: \"";
      message +=  name;
      message += "\" was not found.   Please set ";
      message += langComp;
      message += " to a valid compiler path or name.";
      cmSystemTools::Error(message.c_str());
      path = name;
      }
    std::string doc = lang;
    doc += " compiler.";
    const char* cname = this->GetCMakeInstance()->
      GetCacheManager()->GetCacheValue(langComp.c_str());
    std::string changeVars;
    if(cname && (path != cname) && (optional==false))
      {
      const char* cvars =
        this->GetCMakeInstance()->GetProperty(
          "__CMAKE_DELETE_CACHE_CHANGE_VARS_");
      if(cvars)
        {
        changeVars += cvars;
        changeVars += ";";
        }
      changeVars += langComp;
      changeVars += ";";
      changeVars += cname;
      this->GetCMakeInstance()->SetProperty(
        "__CMAKE_DELETE_CACHE_CHANGE_VARS_",
        changeVars.c_str());
      }
    mf->AddCacheDefinition(langComp.c_str(), path.c_str(),
                           doc.c_str(), cmCacheManager::FILEPATH);
    }
}
