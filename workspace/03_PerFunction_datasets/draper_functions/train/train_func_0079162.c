GenerateScript(std::ostream& os)
{

  ExportSet const* exportSet =
    this->Makefile->GetLocalGenerator()->GetGlobalGenerator()
    ->GetExportSet(this->Name.c_str());


  if(!exportSet)
    {
    cmOStringStream e;
    e << "INSTALL(EXPORT) given unknown export \"" << this->Name << "\"";
    cmSystemTools::Error(e.str().c_str());
    return;
    }


  this->ComputeTempDir();
  cmSystemTools::MakeDirectory(this->TempDir.c_str());


  this->MainImportFile = this->TempDir;
  this->MainImportFile += "/";
  this->MainImportFile += this->FileName;


  this->EFGen->SetName(this->Name.c_str());
  this->EFGen->SetExportSet(exportSet);
  this->EFGen->SetExportFile(this->MainImportFile.c_str());
  this->EFGen->SetNamespace(this->Namespace.c_str());
  if(this->ConfigurationTypes->empty())
    {
    if(this->ConfigurationName && *this->ConfigurationName)
      {
      this->EFGen->AddConfiguration(this->ConfigurationName);
      }
    else
      {
      this->EFGen->AddConfiguration("");
      }
    }
  else
    {
    for(std::vector<std::string>::const_iterator
          ci = this->ConfigurationTypes->begin();
        ci != this->ConfigurationTypes->end(); ++ci)
      {
      this->EFGen->AddConfiguration(ci->c_str());
      }
    }
  this->EFGen->GenerateImportFile();


  this->cmInstallGenerator::GenerateScript(os);
}
