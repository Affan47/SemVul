get_exe_path()
{
	char exe_file[PATH_MAX + 1];
#ifdef __APPLE__
	CFBundleRef mainBundle = CFBundleGetMainBundle();
	if (mainBundle)
	{
		CFURLRef mainURL = CFBundleCopyBundleURL(mainBundle);

		if (mainURL)
		{
			int ok = CFURLGetFileSystemRepresentation (
				mainURL, (Boolean) true, (UInt8*)exe_file, PATH_MAX
			);

			if (ok)
			{
				return std::string(exe_file) + "/";
			}
		}
	}

	throw CL_Error("get_exe_path failed");

#else
#ifndef PROC_EXE_PATH
#define PROC_EXE_PATH "/proc/self/exe"
#endif
	int size;
	struct stat sb;
	if (lstat(PROC_EXE_PATH, &sb) < 0)
	{
#ifdef EXTERN___PROGNAME
		extern const char *__progname;
		char *pathenv, *name, *end;
		char fname[PATH_MAX];
		char cwd[PATH_MAX];
		struct stat sba;

		exe_file[0] = '\0';
		if ((pathenv = getenv("PATH")) != NULL)
		{
			for (name = pathenv; name; name = end)
			{
				if ((end = strchr(name, ':')))
					*end++ = '\0';
				snprintf(fname, sizeof(fname),
					"%s/%s", name, (char *)__progname);
				if (stat(fname, &sba) == 0) {
					snprintf(exe_file, sizeof(exe_file),
						"%s/", name);
					break;
				}
			}
		}


		if (!exe_file[0])
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				snprintf(fname, sizeof(fname),
					"%s/%s", cwd, (char *)__progname);
				if (stat(fname, &sba) == 0)
					snprintf(exe_file, sizeof(exe_file),
						"%s/", cwd);
			}
		}
		if (!exe_file[0])
			throw CL_Error("get_exe_path: could not find path");
		else
			return std::string(exe_file);
#else
		throw CL_Error("get_exe_path: proc file system not accesible");
#endif
	}
	else
	{
		size = readlink(PROC_EXE_PATH, exe_file, PATH_MAX);
		if (size < 0)
		{
			throw CL_Error(strerror(errno));
		}
		else
		{
			exe_file[size] = '\0';
			return std::string(dirname(exe_file)) + "/";
		}
	}
#endif

}
