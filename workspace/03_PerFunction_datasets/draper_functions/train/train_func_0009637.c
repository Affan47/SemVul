removedir(std::string &dname) {
  std::list<DirectAccess>::iterator i=control_dir(dname,true);
  if(i==access.end()) return 1;
  if(!(i->access.del)) return 1;
  std::string fdname=real_name(dname);
  int ur=i->unix_rights(fdname,uid,gid);
  if(ur == 0 && errno > 0) {
    error_description = Arc::StrError(errno);
    return 1;
  }
  if(!(ur & S_IFDIR)) {
    error_description = "Not a directory";
    return 1;
  }
  if(i->unix_set(uid,gid) != 0) return 1;
  if(::remove(fdname.c_str()) != 0) {
    error_description = Arc::StrError(errno);
    i->unix_reset();
    return 1;
  };
  i->unix_reset();
  return 0;
}
