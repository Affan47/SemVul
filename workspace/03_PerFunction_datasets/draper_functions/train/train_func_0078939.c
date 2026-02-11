readModuleBinaries() {
  uint8_t buffer[64*1024];
  std::string fname;
  int rv;


  fname=m_path;
  fname+="/";
  fname+=m_binFileName;
  rv=readFile(fname.c_str(), buffer, sizeof(buffer)-1);
  if (rv<1) {
    fprintf(stderr, "ERROR: Could not read binary [%s]\n", fname.c_str());
    return false;
  }
  m_binFileData=std::string((const char*)buffer, rv);


  fname=m_path;
  fname+="/";
  fname+=m_sigFileName;
  rv=readFile(fname.c_str(), buffer, sizeof(buffer)-1);
  if (rv<1) {
    fprintf(stderr, "ERROR: Could not signature binary [%s]\n", fname.c_str());
    return false;
  }
  m_sigFileData=std::string((const char*)buffer, rv);

  return true;
}
