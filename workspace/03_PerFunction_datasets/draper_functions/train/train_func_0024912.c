files_initialize(void)
{
	const char *dir2;
	static INPUTLINE filter1, filter2;
	static PANEL_DESC panel_desc_1 = { 0,0,0,0,PANEL_TYPE_FILE,0,0,&filter1,0 };
	static PANEL_DESC panel_desc_2 = { 0,0,0,0,PANEL_TYPE_FILE,0,0,&filter2,0 };
	static PANEL_FILE panel_f1 =
		{ &panel_desc_1, { 0,0 }, 0,0,1,0,0 };
	static PANEL_FILE panel_f2 =
		{ &panel_desc_2, { 0,0 }, 0,0,1,0,0 };

	if (get_cwd_us(&panel_f1.dir) < 0)
		err_exit("Cannot get the name of the working directory");
	dir2 = config_str(CFG_DIR2);
	if (*dir2 != '/') {
		dir2 = clex_data.homedir;
		if (*dir2 != '/')
			dir2 = USTR(panel_f1.dir);
	}
	us_copy(&panel_f2.dir,dir2);
	panel_f1.other = &panel_f2;
	ppanel_file = panel_f2.other = &panel_f1;
}
