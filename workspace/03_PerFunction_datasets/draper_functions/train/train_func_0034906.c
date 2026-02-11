SetMsvcTargetPdbVariable(cmNinjaVars& vars) const
{
  cmMakefile* mf = this->GetMakefile();
  if (mf->GetDefinition("MSVC_C_ARCHITECTURE_ID") ||
      mf->GetDefinition("MSVC_CXX_ARCHITECTURE_ID"))
    {
    std::string pdbPath;
    if(this->Target->GetType() == cmTarget::EXECUTABLE ||
       this->Target->GetType() == cmTarget::STATIC_LIBRARY ||
       this->Target->GetType() == cmTarget::SHARED_LIBRARY ||
       this->Target->GetType() == cmTarget::MODULE_LIBRARY)
      {
      pdbPath = this->Target->GetPDBDirectory(this->GetConfigName());
      pdbPath += "/";
      pdbPath += this->Target->GetPDBName(this->GetConfigName());
      }

    vars["TARGET_PDB"] = this->GetLocalGenerator()->ConvertToOutputFormat(
                          ConvertToNinjaPath(pdbPath.c_str()).c_str(),
                          cmLocalGenerator::SHELL);
    EnsureParentDirectoryExists(pdbPath);
    return true;
    }
  return false;
}
