AddStripRule(std::ostream& os,
                                       Indent const& indent,
                                       cmTarget::TargetType type,
                                       const std::string& toDestDirPath)
{


  if(type == cmTarget::STATIC_LIBRARY)
    {
    return;
    }


  if(this->Target->GetMakefile()->IsOn("APPLE") &&
     this->Target->GetPropertyAsBool("MACOSX_BUNDLE"))
    {
    return;
    }

  if(! this->Target->GetMakefile()->IsSet("CMAKE_STRIP"))
    {
    return;
    }

  os << indent << "IF(CMAKE_INSTALL_DO_STRIP)\n";
  os << indent << "  EXECUTE_PROCESS(COMMAND \""
     << this->Target->GetMakefile()->GetDefinition("CMAKE_STRIP")
     << "\" \"" << toDestDirPath << "\")\n";
  os << indent << "ENDIF(CMAKE_INSTALL_DO_STRIP)\n";
}
