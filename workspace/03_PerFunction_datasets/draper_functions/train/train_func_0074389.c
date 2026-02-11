check_lock(char *lockfile, unsigned int maxage_secs,
		   unsigned int *remaining_secs)
{
  unsigned int age, r;
  struct stat statb;

  if (stat(lockfile, &statb) != -1) {
	time_t now;

	now = time(NULL);
	if (now < statb.st_mtime) {

	  now = statb.st_mtime;
	}

	age = now - statb.st_mtime;
	if (age >= maxage_secs)
	  r = 0;
	else
	  r = maxage_secs - age;

	if (remaining_secs != NULL)
	  *remaining_secs = r;

	return(1);
  }
  else if (errno != ENOENT) {
	log_err((LOG_WARN_LEVEL, "Could not stat \"%s\"", lockfile));
	return(-1);
  }

  return(0);
}
