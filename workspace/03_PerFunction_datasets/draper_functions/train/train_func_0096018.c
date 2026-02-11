mg_place_userlist_and_chanview(gtk_window_ui_t *gui)
{
	GtkOrientation orientation;
	GtkWidget *chanviewbox = NULL;
	int pos;

	mg_sanitize_positions(&tab_pos_config, &gui_ulist_pos_config);

	if (gui->chanview) {
		pos = tab_pos_config;

		orientation = chanview_get_orientation(gui->chanview);
		if ((pos == POS_BOTTOM || pos == POS_TOP)
		    && orientation == GTK_ORIENTATION_VERTICAL)
			chanview_set_orientation(gui->chanview, FALSE);
		else if ((pos == POS_TOPLEFT || pos == POS_BOTTOMLEFT || pos == POS_TOPRIGHT
			  || pos == POS_BOTTOMRIGHT) && orientation == GTK_ORIENTATION_HORIZONTAL)
			chanview_set_orientation(gui->chanview, TRUE);
		chanviewbox = chanview_get_box(gui->chanview);
	}

	mg_place_userlist_and_chanview_real(gui, gui->user_box, chanviewbox);
}
