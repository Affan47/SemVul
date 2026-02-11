check_gridmap(const char* dn,char** user,const char* mapfile) {
  std::string globus_gridmap;
  if(mapfile) {
    globus_gridmap=mapfile;
  }
  else {
    char* tmp=getenv("GRIDMAP");
    if((tmp == NULL) || (tmp[0] == 0)) {
      globus_gridmap="/etc/grid-security/grid-mapfile";
    }
    else { globus_gridmap=tmp; };
  };
  std::ifstream f(globus_gridmap.c_str());
  if(!f.is_open() ) {
    logger.msg(Arc::ERROR, "Mapfile is missing at %s", globus_gridmap);
    return false;
  };
  for(;f.good();) {
    std::string buf;
    getline(f,buf);

    char* p = &buf[0];
    for(;*p;p++) if(((*p) != ' ') && ((*p) != '\t')) break;
    if((*p) == '#') continue;
    if((*p) == 0) continue;
    std::string val;
    int n = gridftpd::input_escaped_string(p,val);
    if(strcmp(val.c_str(),dn) != 0) continue;
    p+=n;
    if(user) {
      n=gridftpd::input_escaped_string(p,val);
      *user=strdup(val.c_str());
    };
    f.close();
    return true;
  };
  f.close();
  return false;
}
