ReadListFile(const char *path)
{

  cmGlobalGenerator *gg = this->GetGlobalGenerator();
  bool created = false;


  if (!gg)
    {
    gg = new cmGlobalGenerator;
    gg->SetCMakeInstance(this);
    created = true;
    }


  if(path)
    {
    std::auto_ptr<cmLocalGenerator> lg(gg->CreateLocalGenerator());
    lg->GetMakefile()->SetHomeOutputDirectory
      (cmSystemTools::GetCurrentWorkingDirectory().c_str());
    lg->GetMakefile()->SetStartOutputDirectory
      (cmSystemTools::GetCurrentWorkingDirectory().c_str());
    lg->GetMakefile()->SetHomeDirectory
      (cmSystemTools::GetCurrentWorkingDirectory().c_str());
    lg->GetMakefile()->SetStartDirectory
      (cmSystemTools::GetCurrentWorkingDirectory().c_str());
    if (!lg->GetMakefile()->ReadListFile(0, path))
      {
      cmSystemTools::Error("Error processing file:", path);
      }
    }


  if (created)
    {
    delete gg;
    }
}
