SetSourcePath(const char *pPath) {
  string sPath(pPath);
  string sFolder, sFile;
  SplitPathAndFile(sPath, sSourcePath, sFile);
  EnsureTrailingFolderDelimiter(sSourcePath);
}
