GetFortranModuleDirectory()
{

  if(!this->FortranModuleDirectoryComputed)
    {
    const char* target_mod_dir =
      this->Target->GetProperty("Fortran_MODULE_DIRECTORY");
    const char* moddir_flag =
      this->Makefile->GetDefinition("CMAKE_Fortran_MODDIR_FLAG");
    if(target_mod_dir && moddir_flag)
      {

      if(cmSystemTools::FileIsFullPath(target_mod_dir))
        {

        this->FortranModuleDirectory = target_mod_dir;
        }
      else
        {

        this->FortranModuleDirectory =
          this->Makefile->GetCurrentOutputDirectory();
        this->FortranModuleDirectory += "/";
        this->FortranModuleDirectory += target_mod_dir;
        }


      cmSystemTools::MakeDirectory(this->FortranModuleDirectory.c_str());
      }
    this->FortranModuleDirectoryComputed = true;
    }


  if(this->FortranModuleDirectory.empty())
    {
    return 0;
    }
  else
    {
    return this->FortranModuleDirectory.c_str();
    }
}
