filter_update_dir(void)
{
	int i, save_curs_rel;
	const char *save_curs_dir;


	if (panel_dir.pd->cnt) {
		save_curs_dir = panel_dir.dir[panel_dir.pd->curs].name;
		save_curs_rel = (100 * panel_dir.pd->curs) / panel_dir.pd->cnt;
	}
	else {
		save_curs_dir = 0;
		save_curs_rel = 0;
	}


	dir_main_panel();


	if (save_curs_dir)
		for (i = 0; i < panel_dir.pd->cnt; i++)
			if (panel_dir.dir[i].name == save_curs_dir) {
				panel_dir.pd->curs = i;
				return;
			}
	panel_dir.pd->curs = (save_curs_rel * panel_dir.pd->cnt) / 100;
}
