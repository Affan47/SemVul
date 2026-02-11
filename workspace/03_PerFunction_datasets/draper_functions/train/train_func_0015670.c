getconfigstoreline (const TCHAR *option, TCHAR *value)
{
	TCHAR tmp[CONFIG_BLEN * 2], tmp2[CONFIG_BLEN * 2];
	int idx = 0;

	if (!configstore)
		return 0;
	zfile_fseek (configstore, 0, SEEK_SET);
	for (;;) {
		if (!zfile_fgets (tmp, sizeof tmp / sizeof (TCHAR), configstore))
			return 0;
		if (!cfgfile_separate_line (tmp, tmp2, value))
			continue;
		if (!_tcsicmp (option, tmp2))
			return 1;
	}
}
