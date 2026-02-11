readIniFile(_TCHAR* program, int *argc, _TCHAR ***argv)
{
	_TCHAR* config_file = NULL;
	int result;

	if (program == NULL || argc == NULL || argv == NULL) return -1;

#if defined(_WIN32) && defined(_WIN32_CONSOLE)
	config_file = getIniFile(program, 1);
#else
	config_file = getIniFile(program, 0);
#endif

	result = readConfigFile(config_file, argc, argv);
	free(config_file);
	return result;
}
