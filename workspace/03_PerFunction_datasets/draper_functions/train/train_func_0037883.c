print_infos(int force)
{
	CHAR16 *config_file;
	CHAR16 dpath[FILENAME_MAXLEN];
	CHAR16 *boot_dev_name;
	UINT8 is_abs;

	boot_dev_name = fops_bootdev_name();
	config_file   = get_config_file();

	fops_getdefault_path(dpath, FILENAME_MAXLEN);

	if (force || elilo_opt.verbose > 0)
		Print(L"default file path: %s:%s\n", boot_dev_name, dpath);

	is_abs = config_file && (config_file[0] == CHAR_BACKSLASH || config_file[0] == CHAR_SLASH) ? 1 : 0;

	if (force || elilo_opt.verbose > 0)
			Print(L"config file      : %s%s\n", config_file && is_abs == 0 ? dpath : L"", config_file ? config_file : L"none used");

	if (alt_argv) {
		CHAR16 **p = alt_argv;
		Print(L"found alternate default choice :");
		while (*p) Print(L" %s", *p++);
		Print(L"\n");
	}
}
