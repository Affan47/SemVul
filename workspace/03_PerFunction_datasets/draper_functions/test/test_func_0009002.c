GenerateMainFile(std::ostream& os)
{

  for(std::vector<cmTargetExport*>::const_iterator
        tei = this->ExportSet->begin();
      tei != this->ExportSet->end(); ++tei)
    {
    cmTargetExport* te = *tei;
    if(this->ExportedTargets.insert(te->Target).second)
      {
      this->GenerateImportTargetCode(os, te->Target);
      }
    else
      {
      cmOStringStream e;
      e << "INSTALL(EXPORT \"" << this->Name << "\" ...) "
        << "includes target \"" << te->Target->GetName()
        << "\" more than once in the export set.";
      cmSystemTools::Error(e.str().c_str());
      return false;
      }
    }


  os << "# Load information for each installed configuration.\n"
     << "GET_FILENAME_COMPONENT(_DIR \"${CMAKE_CURRENT_LIST_FILE}\" PATH)\n"
     << "FILE(GLOB CONFIG_FILES \"${_DIR}/"
     << this->GetConfigImportFileGlob() << "\")\n"
     << "FOREACH(f ${CONFIG_FILES})\n"
     << "  INCLUDE(${f})\n"
     << "ENDFOREACH(f)\n"
     << "\n";


  bool result = true;
  for(std::vector<std::string>::const_iterator
        ci = this->Configurations.begin();
      ci != this->Configurations.end(); ++ci)
    {
    if(!this->GenerateImportFileConfig(ci->c_str()))
      {
      result = false;
      }
    }
  return result;
}
