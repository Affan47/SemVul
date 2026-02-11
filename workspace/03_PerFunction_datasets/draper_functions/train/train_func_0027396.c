LoadFile(string &fName)
{
  void *handle;
  const char *pszError;
  bool bReturn = false;

  string sPath= fName;
  FixupLibraryName(sPath);
  string sName;
  MakeCanonicalName(sPath, sName);
  ModuleLibraries_t::iterator mli = ModuleLibraries.find(sName);

  if (mli == ModuleLibraries.end()) {
    if ((handle = ::load_library(sPath.c_str(), &pszError)) == NULL) {
#ifdef THROW
      ostringstream stream;

      stream << "failed to open library module ";
      stream << sPath;
      stream << ": ";
      stream << pszError;
      stream << endl;

      char cw[_MAX_PATH];
      getcwd(cw, sizeof(cw));
      stream << "current working directory is ";
      stream << cw;
      stream << endl << ends;
      free_error_message(pszError);
      throw new Error(stream.str());
#endif
    }
    else {

      ModuleLibraries[sName] = new DynamicModuleLibraryInfo(fName, sName, handle);
      bReturn = true;
    }
  }


  return bReturn;

}
