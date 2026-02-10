filter_off(void)
{
	if (panel->type == PANEL_TYPE_FILE)
		filter_off_file();
	else {

		panel->filtering = 0;
		filter_update();
		win_filter();
	}

	pan_adjust(panel);
	win_filter();
	win_panel();
}
