checkdir(std::string &dirname) {
  logger.msg(Arc::VERBOSE, "plugin: checkdir: %s", dirname);
  std::list<DirectAccess>::iterator i=control_dir(dirname,false);
  if(i==access.end()) return 0;
  logger.msg(Arc::VERBOSE, "plugin: checkdir: access: %s", (*i).name);
  std::string fname = real_name(dirname);
  if(i->access.cd) {
    int ur=(*i).unix_rights(fname,uid,gid);
    if(ur == 0 && errno > 0) {
      error_description = Arc::StrError(errno);
      return 1;
    }
    if((ur & S_IXUSR) && (ur & S_IFDIR)) {
  logger.msg(Arc::VERBOSE, "plugin: checkdir: access: allowed: %s", fname);
      return 0;
    };
  };
  return 1;
}
