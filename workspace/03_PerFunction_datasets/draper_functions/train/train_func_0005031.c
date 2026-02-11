gui_radio_group_new(guint num, const gchar **label, GtkWidget *but[])
{
	GSList	*list = NULL;
	guint	i;

	for(i = 0; i < num; i++)
	{
		but[i] = gtk_radio_button_new_with_label(list, _(label[i]));
		list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(but[i]));
		g_object_set_data(G_OBJECT(but[i]), "user", GUINT_TO_POINTER(i));
	}
	return list;
}
