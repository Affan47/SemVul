map_unixuser(const AuthUser& ,unix_user_t& unix_user,const char* line) {

  std::string unixname(line);
  std::string unixgroup;
  std::string::size_type p = unixname.find(':');
  if(p != std::string::npos) {
    unixgroup=unixname.c_str()+p+1;
    unixname.resize(p);
  };
  if(unixname.empty()) return false;
  unix_user.name=unixname;
  unix_user.group=unixgroup;
  return true;
}

}
