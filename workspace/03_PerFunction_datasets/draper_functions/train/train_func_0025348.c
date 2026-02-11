gf_font_manager_new(GF_User *user)
{
	char *def_font = "SERIF";
	u32 i, count;
	GF_FontManager *font_mgr;
	GF_FontReader *ifce;
	const char *opt;

	ifce = NULL;
	opt = gf_cfg_get_key(user->config, "FontEngine", "FontReader");
	if (opt) {
		ifce = (GF_FontReader *) gf_modules_load_interface_by_name(user->modules, opt, GF_FONT_READER_INTERFACE);
		if (ifce && ifce->init_font_engine(ifce) != GF_OK) {
			gf_modules_close_interface((GF_BaseInterface *)ifce);
			ifce = NULL;
		}
	}

	if (!ifce) {
		count = gf_modules_get_count(user->modules);
		for (i=0; i<count; i++) {
			ifce = (GF_FontReader *) gf_modules_load_interface(user->modules, i, GF_FONT_READER_INTERFACE);
			if (!ifce) continue;

			if (ifce->init_font_engine(ifce) != GF_OK) {
				gf_modules_close_interface((GF_BaseInterface *)ifce);
				ifce = NULL;
				continue;
			}

			gf_cfg_set_key(user->config, "FontEngine", "FontReader", ifce->module_name);
			break;
		}
	}
	GF_SAFEALLOC(font_mgr, GF_FontManager);
	font_mgr->reader = ifce;
	font_mgr->id_buffer_size = 20;
	font_mgr->id_buffer = gf_malloc(sizeof(u32)*font_mgr->id_buffer_size);
	gf_font_manager_set_font(font_mgr, &def_font, 1, 0);
	font_mgr->default_font = font_mgr->font;

	font_mgr->line_path= gf_path_new();
	gf_path_add_move_to(font_mgr->line_path, -FIX_ONE/2, FIX_ONE/2);
	gf_path_add_line_to(font_mgr->line_path, FIX_ONE/2, FIX_ONE/2);
	gf_path_add_line_to(font_mgr->line_path, FIX_ONE/2, -FIX_ONE/2);
	gf_path_add_line_to(font_mgr->line_path, -FIX_ONE/2, -FIX_ONE/2);
	gf_path_close(font_mgr->line_path);

	opt = gf_cfg_get_key(user->config, "FontEngine", "WaitForFontLoad");
	if (!opt) gf_cfg_set_key(user->config, "FontEngine", "WaitForFontLoad", "no");
	if (opt && !strcmp(opt, "yes")) font_mgr->wait_font_load = 1;

	return font_mgr;
}
