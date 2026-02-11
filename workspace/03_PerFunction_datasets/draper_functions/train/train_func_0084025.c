Run(const std::vector<std::string>& args, bool noconfigure)
{

  this->SetArgs(args);
  if(cmSystemTools::GetErrorOccuredFlag())
    {
    return -1;
    }


  if(!this->CheckStampList.empty() &&
     cmakeCheckStampList(this->CheckStampList.c_str()))
    {
    return 0;
    }


  if(!this->CheckStampFile.empty() &&
     cmakeCheckStampFile(this->CheckStampFile.c_str()))
    {
    return 0;
    }


  this->CMakeCommand = args[0];

  if ( this->GetWorkingMode() == NORMAL_MODE )
    {

    if(this->LoadCache() < 0)
      {
      cmSystemTools::Error("Error executing cmake::LoadCache(). Aborting.\n");
      return -1;
      }
    }
  else
    {
    this->AddCMakePaths();
    }

  if ( !this->SetCacheArgs(args) )
    {
    cmSystemTools::Error("Problem processing arguments. Aborting.\n");
    return -1;
    }


  if(this->GetWorkingMode() != NORMAL_MODE)
    {
    if(cmSystemTools::GetErrorOccuredFlag())
      {
      return -1;
      }
    else
      {
      return 0;
      }
    }


  if(getenv("MAKEFLAGS"))
    {
    cmSystemTools::PutEnv("MAKEFLAGS=");
    }

  this->PreLoadCMakeFiles();

  if ( noconfigure )
    {
    return 0;
    }


  if(!this->CheckBuildSystem())
    {
    return 0;
    }


  std::string oldstartdir = this->GetStartDirectory();
  std::string oldstartoutputdir = this->GetStartOutputDirectory();
  this->SetStartDirectory(this->GetHomeDirectory());
  this->SetStartOutputDirectory(this->GetHomeOutputDirectory());
  int ret = this->Configure();
  if (ret || this->GetWorkingMode() != NORMAL_MODE)
    {
#if defined(CMAKE_HAVE_VS_GENERATORS)
    if(!this->VSSolutionFile.empty() && this->GlobalGenerator)
      {


      cmSystemTools::Message(
        "CMake Configure step failed.  "
        "Build files cannot be regenerated correctly.  "
        "Attempting to stop IDE build.");
      cmGlobalVisualStudioGenerator* gg =
        static_cast<cmGlobalVisualStudioGenerator*>(this->GlobalGenerator);
      gg->CallVisualStudioMacro(cmGlobalVisualStudioGenerator::MacroStop,
                                this->VSSolutionFile.c_str());
      }
#endif
    return ret;
    }
  ret = this->Generate();
  std::string message = "Build files have been written to: ";
  message += this->GetHomeOutputDirectory();
  this->UpdateProgress(message.c_str(), -1);
  if(ret)
    {
    return ret;
    }
  this->SetStartDirectory(oldstartdir.c_str());
  this->SetStartOutputDirectory(oldstartoutputdir.c_str());

  return ret;
}
