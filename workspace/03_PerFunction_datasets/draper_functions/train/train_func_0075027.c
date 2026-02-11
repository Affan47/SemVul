refresh_resolvers(void)
{
#ifdef G_OS_UNIX
	static time_t resolv_conf_changed = (time_t)NULL;
	struct stat s;


	if (stat("/etc/resolv.conf", &s) == 0) {
		if (s.st_mtime > resolv_conf_changed) {
			resolv_conf_changed = s.st_mtime;
			res_init();
		}
	}

#endif
}
