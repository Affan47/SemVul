txv_enable(GtkWidget *wid)
{
	TxvInfo	*txi;

	if((wid != NULL) && ((txi = g_object_get_data(G_OBJECT(wid), "user")) != NULL))
	{
		gtk_widget_show(wid);

		gtk_widget_set_sensitive(txi->bhbox, TRUE);
	}
	else
		fprintf(stderr, "TEXTVIEW: Couldn't enable\n");
}
