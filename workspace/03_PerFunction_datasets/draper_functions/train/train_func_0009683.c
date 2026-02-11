SubmitUsingCP(
  const cmStdString& localprefix,
  const std::set<cmStdString>& files,
  const cmStdString& remoteprefix,
  const cmStdString& destination)
{
  if ( !localprefix.size() ||
    !files.size() || !remoteprefix.size() || !destination.size() )
    {
    cmCTestLog(this->CTest, ERROR_MESSAGE,
               "Missing arguments for submit via cp:\n"
               << "\tlocalprefix: " << localprefix << "\n"
               << "\tNumber of files: " << files.size() << "\n"
               << "\tremoteprefix: " << remoteprefix << "\n"
               << "\tdestination: " << destination << std::endl);
    return 0;
    }
  cmCTest::SetOfStrings::const_iterator file;
  bool problems = false;
  for ( file = files.begin(); file != files.end(); ++file )
    {
    std::string lfname = localprefix;
    cmSystemTools::ConvertToUnixSlashes(lfname);
    lfname += "/" + *file;
    std::string rfname = destination + "/" + remoteprefix + *file;
    cmSystemTools::CopyFileAlways(lfname.c_str(), rfname.c_str());
    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "   Copy file: "
        << lfname.c_str() << " to "
        << rfname.c_str() << std::endl);
    }
  std::string tagDoneFile = destination + "/" + remoteprefix + "DONE";
  cmSystemTools::Touch(tagDoneFile.c_str(), true);
  if ( problems )
    {
    return false;
    }
  return true;
}
