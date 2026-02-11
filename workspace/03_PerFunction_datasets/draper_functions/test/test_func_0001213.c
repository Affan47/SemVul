get_home_dir()
{
#if defined (USE_WINDOWS_PACKAGING)
	static FileName const home_dir(getEnv("USERPROFILE"));
#else
	static FileName const home_dir(getEnv("HOME"));
#endif
	return home_dir;
}
