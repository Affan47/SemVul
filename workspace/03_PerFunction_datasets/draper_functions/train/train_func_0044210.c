fix_file_owner(const std::string &fname,const Arc::User& user) {
  if(getuid() == 0) {
    if(lchown(fname.c_str(),user.get_uid(),user.get_gid()) == -1) {
      logger.msg(Arc::ERROR,"Failed setting file owner: %s",fname);
      return false;
    };
  };
  return true;
}
