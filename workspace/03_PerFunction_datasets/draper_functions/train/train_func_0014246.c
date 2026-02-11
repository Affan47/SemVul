PackageComponentsAllInOne()
{
  int retval = 1;
  std::string compInstDirName;


  packageFileNames.clear();
  std::string initialTopLevel(this->GetOption("CPACK_TEMPORARY_DIRECTORY"));

  compInstDirName = "ALL_COMPONENTS_IN_ONE";

  cmCPackLogger(cmCPackLog::LOG_VERBOSE,
                "Packaging all groups in one package..."
                "(CPACK_COMPONENTS_ALL_[GROUPS_]IN_ONE_PACKAGE is set)"
      << std::endl);


  std::string localToplevel(initialTopLevel);
  std::string packageFileName(
      cmSystemTools::GetParentDirectory(toplevel.c_str())
                             );
  std::string outputFileName(
            std::string(this->GetOption("CPACK_PACKAGE_FILE_NAME"))
            + this->GetOutputExtension()
                            );

  localToplevel += "/"+compInstDirName;


  this->SetOption("CPACK_TEMPORARY_DIRECTORY",localToplevel.c_str());
  packageFileName += "/"+ outputFileName;

  this->SetOption("CPACK_OUTPUT_FILE_NAME",outputFileName.c_str());

  this->SetOption("CPACK_TEMPORARY_PACKAGE_FILE_NAME",
      packageFileName.c_str());

  this->SetOption("CPACK_DEB_PACKAGE_COMPONENT",compInstDirName.c_str());
  if (!this->ReadListFile("CPackDeb.cmake"))
    {
    cmCPackLogger(cmCPackLog::LOG_ERROR,
        "Error while execution CPackDeb.cmake" << std::endl);
    retval = 0;
    return retval;
    }

  cmsys::Glob gl;
  std::string findExpr(this->GetOption("WDIR"));
  findExpr += "/*";
  gl.RecurseOn();
  if ( !gl.FindFiles(findExpr) )
    {
    cmCPackLogger(cmCPackLog::LOG_ERROR,
    "Cannot find any files in the installed directory" << std::endl);
    return 0;
    }
  packageFiles = gl.GetFiles();

  int res = createDeb();
  if (res != 1)
    {
    retval = 0;
    }

  packageFileNames.push_back(packageFileName);
  return retval;
}
