ps_dirs_init()
{
	struct stat stat_buf;
	mode_t mode = S_IRWXU;


	if (stat(tcsd_options.system_ps_dir, &stat_buf) == -1) {
		if (errno == ENOENT) {

			if (mkdir(tcsd_options.system_ps_dir, mode) == -1) {
				LogError("mkdir(%s) failed: %s. If you'd like to use %s to "
						"store your system persistent data, please"
						" create it. Otherwise, change the location"
						" in your tcsd config file.",
						tcsd_options.system_ps_dir, strerror(errno),
						tcsd_options.system_ps_dir);
				return TCSERR(TSS_E_INTERNAL_ERROR);
			}
		} else {
			LogError("stat failed: %s", strerror(errno));
			return TCSERR(TSS_E_INTERNAL_ERROR);
		}
	}


	if (stat(tcsd_options.system_ps_dir, &stat_buf) == -1) {
		LogError("stat %s failed: %s", tcsd_options.system_ps_dir, strerror(errno));
		return TCSERR(TSS_E_INTERNAL_ERROR);
	}


	if (!S_ISDIR(stat_buf.st_mode)) {
		LogError("PS dir %s is not a directory! Exiting.", tcsd_options.system_ps_dir);
		return TCSERR(TSS_E_INTERNAL_ERROR);
	} else if (((stat_buf.st_mode & 0777) ^ mode) != 0) {

		LogInfo("resetting mode of %s from %o to: %o", tcsd_options.system_ps_dir,
			(unsigned int) stat_buf.st_mode, (unsigned int) mode);
		if (chmod(tcsd_options.system_ps_dir, mode) == -1) {
			LogError("chmod(%s) failed: %s", tcsd_options.system_ps_dir,
				 strerror(errno));
			return TCSERR(TSS_E_INTERNAL_ERROR);
		}
	}

	return TSS_SUCCESS;
}
