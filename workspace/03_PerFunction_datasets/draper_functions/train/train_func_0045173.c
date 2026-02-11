_set_work_dir(void)
{
	bool success = false;

	if (slurmctld_conf.slurmctld_logfile &&
	    (slurmctld_conf.slurmctld_logfile[0] == '/')) {
		char *slash_ptr, *work_dir;
		work_dir = xstrdup(slurmctld_conf.slurmctld_logfile);
		slash_ptr = strrchr(work_dir, '/');
		if (slash_ptr == work_dir)
			work_dir[1] = '\0';
		else
			slash_ptr[0] = '\0';
		if ((access(work_dir, W_OK) != 0) || (chdir(work_dir) < 0))
			error("chdir(%s): %m", work_dir);
		else
			success = true;
		xfree(work_dir);
	}

	if (!success) {
		if ((access(slurmctld_conf.state_save_location, W_OK) != 0) ||
		    (chdir(slurmctld_conf.state_save_location) < 0)) {
			error("chdir(%s): %m",
			      slurmctld_conf.state_save_location);
		} else
			success = true;
	}

	if (!success) {
		if ((access("/var/tmp", W_OK) != 0) ||
		    (chdir("/var/tmp") < 0)) {
			error("chdir(/var/tmp): %m");
		} else
			info("chdir to /var/tmp");
	}
}
