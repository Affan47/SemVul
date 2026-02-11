ReadSettings(const char* settingsFileName,
                                    const char* fallbackSettingsFileName)
{
  cmake cm;
  cmGlobalGenerator ggi;
  ggi.SetCMakeInstance(&cm);
  cmsys::auto_ptr<cmLocalGenerator> lg(ggi.CreateLocalGenerator());
  cmMakefile *mf = lg->GetMakefile();

  const char* inFileName = settingsFileName;

  if ( !cmSystemTools::FileExists(inFileName) )
    {
    inFileName = fallbackSettingsFileName;
    if ( !cmSystemTools::FileExists(inFileName) )
      {
      return;
      }
    }

  if ( !mf->ReadListFile(0, inFileName) )
    {
    cmSystemTools::Error("Problem opening GraphViz options file: ",
                         inFileName);
    return;
    }

  std::cout << "Reading GraphViz options file: " << inFileName << std::endl;

#define __set_if_set(var, cmakeDefinition) \
  { \
  const char* value = mf->GetDefinition(cmakeDefinition); \
  if ( value ) \
    { \
    var = value; \
    } \
  }

  __set_if_set(this->GraphType, "GRAPHVIZ_GRAPH_TYPE");
  __set_if_set(this->GraphName, "GRAPHVIZ_GRAPH_NAME");
  __set_if_set(this->GraphHeader, "GRAPHVIZ_GRAPH_HEADER");
  __set_if_set(this->GraphNodePrefix, "GRAPHVIZ_NODE_PREFIX");

#define __set_bool_if_set(var, cmakeDefinition) \
  { \
  const char* value = mf->GetDefinition(cmakeDefinition); \
  if ( value ) \
    { \
    var = mf->IsOn(cmakeDefinition); \
    } \
  }

  __set_bool_if_set(this->GenerateForExecutables, "GRAPHVIZ_EXECUTABLES");
  __set_bool_if_set(this->GenerateForStaticLibs, "GRAPHVIZ_STATIC_LIBS");
  __set_bool_if_set(this->GenerateForSharedLibs, "GRAPHVIZ_SHARED_LIBS");
  __set_bool_if_set(this->GenerateForModuleLibs, "GRAPHVIZ_MODULE_LIBS");
  __set_bool_if_set(this->GenerateForExternals, "GRAPHVIZ_EXTERNAL_LIBS");

  cmStdString ignoreTargetsRegexes;
  __set_if_set(ignoreTargetsRegexes, "GRAPHVIZ_IGNORE_TARGETS");

  this->TargetsToIgnoreRegex.clear();
  if (ignoreTargetsRegexes.size() > 0)
    {
    std::vector<std::string> ignoreTargetsRegExVector;
    cmSystemTools::ExpandListArgument(ignoreTargetsRegexes,
                                      ignoreTargetsRegExVector);
    for(std::vector<std::string>::const_iterator itvIt
                                            = ignoreTargetsRegExVector.begin();
        itvIt != ignoreTargetsRegExVector.end();
        ++ itvIt )
      {
      cmStdString currentRegexString(*itvIt);
      cmsys::RegularExpression currentRegex;
      if (!currentRegex.compile(currentRegexString.c_str()))
        {
        std::cerr << "Could not compile bad regex \"" << currentRegexString
                  << "\"" << std::endl;
        }
      this->TargetsToIgnoreRegex.push_back(currentRegex);
      }
    }

}
