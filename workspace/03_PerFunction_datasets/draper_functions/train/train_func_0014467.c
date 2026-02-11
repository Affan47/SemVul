rename_pidlog_file(PsetHndl pset, char* newname) {
  char oldpath[BIG_LINE];
  char newpath[BIG_LINE];
  int errorCode;

  if (!newname || !*newname ||
      !util_is_valid_path_string(newname)) {
    return 0;
  }

  char *oldname = psetGetAttrSingleValue(pset,
					 "configuration.nsPidLog",
					 &errorCode);
  if (oldname != NULL && strcmp(oldname, newname) != 0) {
    char *piddir = util_get_pid_dir();
    PR_snprintf(oldpath, sizeof(oldpath), "%s/%s", piddir, oldname);
    PR_snprintf(newpath, sizeof(newpath), "%s/%s", piddir, newname);
    if(rename (oldpath, newpath) != 0)
      return 0;
    return !update_conf("console.conf", "PidFile", newname);
  }
  else return 1;
}
