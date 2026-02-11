AddFortranFlags(std::string& flags)
{

  if(const char* mod_dir = this->GetFortranModuleDirectory())
    {
    const char* moddir_flag =
      this->Makefile->GetRequiredDefinition("CMAKE_Fortran_MODDIR_FLAG");
    std::string modflag = moddir_flag;
    modflag += this->Convert(mod_dir,
                             cmLocalGenerator::START_OUTPUT,
                             cmLocalGenerator::SHELL);
    this->LocalGenerator->AppendFlags(flags, modflag.c_str());
    }


  if(const char* modpath_flag =
     this->Makefile->GetDefinition("CMAKE_Fortran_MODPATH_FLAG"))
    {
    std::vector<std::string> includes;
    this->LocalGenerator->GetIncludeDirectories(includes);
    for(std::vector<std::string>::const_iterator idi = includes.begin();
        idi != includes.end(); ++idi)
      {
      std::string flg = modpath_flag;
      flg += this->Convert(idi->c_str(),
                           cmLocalGenerator::NONE,
                           cmLocalGenerator::SHELL);
      this->LocalGenerator->AppendFlags(flags, flg.c_str());
      }
    }
}
