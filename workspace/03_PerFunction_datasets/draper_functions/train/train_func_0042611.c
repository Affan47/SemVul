InitializeInternal()
{
  this->SetOptionIfNotSet("CPACK_INCLUDE_TOPLEVEL_DIRECTORY", "1");
  this->ReadListFile("CPackZIP.cmake");
  if ((!this->IsSet("ZIP_EXECUTABLE"))
      || (!this->IsSet("CPACK_ZIP_COMMAND")))
    {
    cmCPackLogger(cmCPackLog::LOG_ERROR, "Cannot find a suitable ZIP program"
      << std::endl);
    return 0;
    }
  return this->Superclass::InitializeInternal();
}
