GetFileNameBase(string &sPath, string &sName) {
  GetFileName(sPath, sName);
  string::size_type pos = sName.find_last_of('.');
  if(pos != string::npos) {
    sName = sName.substr(0, sName.size() - pos + 1);
  }
  else {
    sName = sPath;
  }
}
