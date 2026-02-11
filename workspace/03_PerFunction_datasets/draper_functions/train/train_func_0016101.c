fe_buttons_update (session *sess)
{
	session_gui *gui = sess->gui;

	gtk_widget_destroy (gui->button_box);
	gui->button_box = mg_create_userlistbuttons (gui->button_box_parent);

	if (prefs.hex_gui_ulist_buttons)
		gtk_widget_show (sess->gui->button_box);
	else
		gtk_widget_hide (sess->gui->button_box);
}
