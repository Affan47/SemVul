evt_dnarrow_clicked(GtkWidget *wid, gpointer user)
{
	P_Buttons	*page = user;
	Button		*but;

	if((page != NULL) && ((but = btn_button_get(page->button)) != NULL))
	{
		page->modified = TRUE;
		btn_button_set_flags_boolean(but, BTF_NARROW, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid)));
		set_mode_normal(page);
		reset_widgets(page);
		populate_scwin(page);

	}
	return TRUE;
}
