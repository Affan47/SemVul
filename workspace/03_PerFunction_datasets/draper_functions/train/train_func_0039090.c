bm_list_prepare(void)
{
	time_t mod;

	mod = mod_time(user_bm_file);
	if (bm_file_mod != mod && read_bm_file() == 0) {
		bm_file_mod = mod;
		win_warning("Latest version of the bookmarks was loaded from the file.");
	}

	panel_bm_lst.pd->cnt = bm_cnt;
	if (panel_bm_lst.pd->curs < 0)
		panel_bm_lst.pd->curs = panel_bm_lst.pd->top =  panel_bm_lst.pd->min;


	panel = panel_bm_lst.pd;
	textline = 0;
}
