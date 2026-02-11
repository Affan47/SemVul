gethomedir(void)
{
	static const char *home;
	const char *dir;

	if G_LIKELY(home != NULL)
		return home;

#ifdef MINGW32
	dir = mingw_get_home_path();
#else
	dir = getenv("HOME");

	if (dir != NULL && !is_absolute_path(dir)) {

		g_warning("ignoring environment HOME: not an absolute path");
		dir = NULL;
	}

	if (dir != NULL && !is_directory(dir)) {
		g_warning("ignoring environment HOME: not a directory");
		dir = NULL;
	}

	if (dir != NULL && -1 == access(dir, R_OK | W_OK | X_OK)) {
		g_warning("ignoring non-accessible environment HOME: %m");
		dir = NULL;
	}

#if defined(HAS_GETLOGIN)
	if (!dir) {
		const char *name;

		name = getlogin();
		if (name) {
			const struct passwd *pp;

			pp = getpwnam(name);
			if (pp)
				dir = pp->pw_dir;
		}
	}
#endif

#if defined(HAS_GETUID)
	if (!dir) {
		const struct passwd *pp;

		pp = getpwuid(getuid());
		if (pp)
			dir = pp->pw_dir;
	}
#endif

	if (NULL == dir) {
		g_warning("could not determine home directory");
		dir = "/";
	}
#endif

	return home = constant_str(dir);
}
