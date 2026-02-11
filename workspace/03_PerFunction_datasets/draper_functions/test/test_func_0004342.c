GetInstallFilename(cmTarget* target,
                                                         const char* config,
                                                         NameType nameType)
{
  std::string fname;

  if(target->GetType() == cmTarget::EXECUTABLE)
    {
    std::string targetName;
    std::string targetNameReal;
    std::string targetNameImport;
    std::string targetNamePDB;
    target->GetExecutableNames(targetName, targetNameReal,
                               targetNameImport, targetNamePDB,
                               config);
    if(nameType == NameImplib)
      {

      if(!target->GetImplibGNUtoMS(targetNameImport, fname,
                                   "${CMAKE_IMPORT_LIBRARY_SUFFIX}"))
        {
        fname = targetNameImport;
        }
      }
    else if(nameType == NameReal)
      {

      fname = targetNameReal;
      }
    else
      {

      fname = targetName;
      }
    }
  else
    {
    std::string targetName;
    std::string targetNameSO;
    std::string targetNameReal;
    std::string targetNameImport;
    std::string targetNamePDB;
    target->GetLibraryNames(targetName, targetNameSO, targetNameReal,
                            targetNameImport, targetNamePDB, config);
    if(nameType == NameImplib)
      {

      if(!target->GetImplibGNUtoMS(targetNameImport, fname,
                                   "${CMAKE_IMPORT_LIBRARY_SUFFIX}"))
        {
        fname = targetNameImport;
        }
      }
    else if(nameType == NameSO)
      {

      fname = targetNameSO;
      }
    else if(nameType == NameReal)
      {

      fname = targetNameReal;
      }
    else
      {

      fname = targetName;
      }
    }

  return fname;
}
