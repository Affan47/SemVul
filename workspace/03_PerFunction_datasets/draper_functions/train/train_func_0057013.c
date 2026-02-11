remove_pidfile(char *pid_file) {
  if (!pid_file)
      return;

  if (unlink(pid_file)) {
      fprintf(stderr,"Could not remove the pid file %s.\n",pid_file);
  }

}
