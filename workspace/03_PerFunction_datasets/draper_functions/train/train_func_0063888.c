initialize_finddir()
{
	char path[FINDDIR_CHAR_LEN];

	info.nofilecheck=0;

	sprintf(info.nullchar, "(null)");

	if(strncpycmd(path, "echo -n ~", FINDDIR_CHAR_LEN) != 0)
		return -1;

	info.datadir[FINDDIR_CUSTOM][0] = '\0';
	snprintf(info.datadir[FINDDIR_LOCAL], FINDDIR_CHAR_LEN, "%s/.conkycolors", path);
	snprintf(info.datadir[FINDDIR_SYSTEM], FINDDIR_CHAR_LEN, "/usr/share/conkycolors");
	snprintf(info.tempdir, FINDDIR_CHAR_LEN, "/tmp/conkycolors");

	if(systemf("if ! test -d %s; then mkdir -p %s; fi", info.tempdir, info.tempdir) != 0)
	{
		printf("Failed to make %s\n", info.tempdir);
		return -1;
	}

	return 0;
}
