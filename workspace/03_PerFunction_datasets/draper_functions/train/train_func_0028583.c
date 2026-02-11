_stat_slurm_dirs(void)
{
	struct stat stat_buf;
	char *problem_dir = NULL;

	if ((stat(slurmctld_conf.plugindir, &stat_buf) == 0) &&
	    (stat_buf.st_mode & S_IWOTH)) {
		problem_dir = "PluginDir";
	}
	if ((stat(slurmctld_conf.plugstack, &stat_buf) == 0) &&
	    (stat_buf.st_mode & S_IWOTH)) {
		problem_dir = "PlugStack";
	}
	if ((stat(slurmctld_conf.slurmd_spooldir, &stat_buf) == 0) &&
	    (stat_buf.st_mode & S_IWOTH)) {
		problem_dir = "SlurmdSpoolDir";
	}
	if ((stat(slurmctld_conf.state_save_location, &stat_buf) == 0) &&
	    (stat_buf.st_mode & S_IWOTH)) {
		problem_dir = "StateSaveLocation";
	}

	if (problem_dir) {
		error("################################################");
		error("###       SEVERE SECURITY VULERABILTY        ###");
		error("### %s DIRECTORY IS WORLD WRITABLE ###", problem_dir);
		error("###         CORRECT FILE PERMISSIONS         ###");
		error("################################################");
	}
}
