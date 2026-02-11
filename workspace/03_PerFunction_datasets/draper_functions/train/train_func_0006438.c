AddArchitectureFlags(std::string& flags,
                                            cmGeneratorTarget* target,
                                            const char *lang,
                                            const char* config)
{

  if(!this->Makefile->IsOn("APPLE"))
    {
    return;
    }

  if(this->EmitUniversalBinaryFlags)
    {
    std::vector<std::string> archs;
    target->GetAppleArchs(config, archs);
    const char* sysroot = this->Makefile->GetDefinition("CMAKE_OSX_SYSROOT");
    if(sysroot && sysroot[0] == '/' && !sysroot[1])
      { sysroot = 0; }
    std::string sysrootFlagVar =
      std::string("CMAKE_") + lang + "_SYSROOT_FLAG";
    const char* sysrootFlag =
      this->Makefile->GetDefinition(sysrootFlagVar.c_str());
    const char* deploymentTarget =
      this->Makefile->GetDefinition("CMAKE_OSX_DEPLOYMENT_TARGET");
    std::string deploymentTargetFlagVar =
      std::string("CMAKE_") + lang + "_OSX_DEPLOYMENT_TARGET_FLAG";
    const char* deploymentTargetFlag =
      this->Makefile->GetDefinition(deploymentTargetFlagVar.c_str());
    if(!archs.empty() && lang && (lang[0] =='C' || lang[0] == 'F'))
      {
      for(std::vector<std::string>::iterator i = archs.begin();
          i != archs.end(); ++i)
        {
        flags += " -arch ";
        flags += *i;
        }
      }

    if(sysrootFlag && *sysrootFlag && sysroot && *sysroot)
      {
      flags += " ";
      flags += sysrootFlag;
      flags += " ";
      flags += sysroot;
      }

    if (deploymentTargetFlag && *deploymentTargetFlag &&
        deploymentTarget && *deploymentTarget)
      {
      flags += " ";
      flags += deploymentTargetFlag;
      flags += deploymentTarget;
      }
    }
}
