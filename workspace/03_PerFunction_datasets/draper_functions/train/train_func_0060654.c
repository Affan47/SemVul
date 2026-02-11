key_dialog_tog_key (GtkWidget * tog, int kstate)
{
	int state = GTK_TOGGLE_BUTTON (tog)->active;
	int row = gtkutil_clist_selection (key_dialog_kb_clist);
	struct key_binding *kb;
	char buf[32];

	if (row == -1)
		return;

	kb = gtk_clist_get_row_data (GTK_CLIST (key_dialog_kb_clist), row);
	if (state)
		kb->mod |= kstate;
	else
		kb->mod &= ~kstate;

	gtk_clist_set_text (GTK_CLIST (key_dialog_kb_clist), row, 0,
							  key_make_mod_str (kb->mod, buf));
}
