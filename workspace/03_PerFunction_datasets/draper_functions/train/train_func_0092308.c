DetermineType(const char* cmd, const char* type)
{
  cmCTestLog(this->CTest, DEBUG, "Determine update type from command: " << cmd
    << " and type: " << type << std::endl);
  if ( type && *type )
    {
    cmCTestLog(this->CTest, DEBUG, "Type specified: " << type << std::endl);
    std::string stype = cmSystemTools::LowerCase(type);
    if ( stype.find("cvs") != std::string::npos )
      {
      return cmCTestUpdateHandler::e_CVS;
      }
    if ( stype.find("svn") != std::string::npos )
      {
      return cmCTestUpdateHandler::e_SVN;
      }
    }
  else
    {
    cmCTestLog(this->CTest, DEBUG, "Type not specified, check command: "
      << cmd << std::endl);
    std::string stype = cmSystemTools::LowerCase(cmd);
    if ( stype.find("cvs") != std::string::npos )
      {
      return cmCTestUpdateHandler::e_CVS;
      }
    if ( stype.find("svn") != std::string::npos )
      {
      return cmCTestUpdateHandler::e_SVN;
      }
    }
  std::string sourceDirectory = this->GetOption("SourceDirectory");
  cmCTestLog(this->CTest, DEBUG, "Check directory: "
    << sourceDirectory.c_str() << std::endl);
  sourceDirectory += "/.svn";
  if ( cmSystemTools::FileExists(sourceDirectory.c_str()) )
    {
    return cmCTestUpdateHandler::e_SVN;
    }
  sourceDirectory = this->GetOption("SourceDirectory");
  sourceDirectory += "/CVS";
  if ( cmSystemTools::FileExists(sourceDirectory.c_str()) )
    {
    return cmCTestUpdateHandler::e_CVS;
    }
  return cmCTestUpdateHandler::e_UNKNOWN;
}
