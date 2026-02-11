prepareuser(struct passwd *passwd, char *dirname) {
  struct stat fstatus;

  (void) umask(0000);
  if (stat(dirname, &fstatus) || !S_ISDIR(fstatus.st_mode)) {
    if (!strcmp(passwd->pw_name, conf.anonuser)) {
      if (create_dir(dirname, 0)) {
        log_event(CPERROR, "failed to create anonymous output directory", dirname);
        return 1;
      }
      if (chmod(dirname, (mode_t)(0777&~conf.anonumask))) {
        log_event(CPERROR, "failed to set mode on anonymous output directory", dirname);
        return 1;
      }
      log_event(CPDEBUG, "anonymous output directory created", dirname);
    }
    else {
      if (create_dir(dirname, 0)) {
        log_event(CPERROR, "failed to create user output directory", dirname);
        return 1;
      }
      if (chmod(dirname, (mode_t)(0777&~conf.userumask))) {
        log_event(CPERROR, "failed to set mode on user output directory", dirname);
        return 1;
      }
      log_event(CPDEBUG, "user output directory created", dirname);
    }
    if (chown(dirname, passwd->pw_uid, passwd->pw_gid)) {
      log_event(CPERROR, "failed to set owner for output directory", passwd->pw_name);
      return 1;
    }
    log_event(CPDEBUG, "owner set for output directory", passwd->pw_name);
  }
  (void) umask(0077);
  return 0;
}
