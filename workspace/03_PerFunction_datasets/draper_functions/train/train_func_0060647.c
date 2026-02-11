fix_file_permissions(const std::string &fname,const GMJob &job,const GMConfig& config) {
  mode_t mode = S_IRUSR | S_IWUSR;
  uid_t uid = job.get_user().get_uid();
  gid_t gid = job.get_user().get_gid();
  if(!config.MatchShareUid(uid)) {
    mode |= S_IRGRP;
    if(!config.MatchShareGid(gid)) {
      mode |= S_IROTH;
    };
  };
  return (chmod(fname.c_str(),mode) == 0);
}
