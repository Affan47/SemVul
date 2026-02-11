setup_create_toggleR (GtkWidget *tab, int row, const setting *set)
{
	GtkWidget *wid;

	wid = gtk_check_button_new_with_label (_(set->label));
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (wid),
											setup_get_int (&setup_prefs, set));
	g_signal_connect (G_OBJECT (wid), "toggled",
							G_CALLBACK (setup_toggle_cb), (gpointer)set);
	if (set->tooltip)
		add_tip (wid, _(set->tooltip));
	gtk_table_attach (GTK_TABLE (tab), wid, 4, 5, row, row + 1,
							GTK_EXPAND | GTK_SHRINK | GTK_FILL, GTK_SHRINK | GTK_FILL, 0, 0);
}
