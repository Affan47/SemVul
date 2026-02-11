traite_option(GtkComboBox *combobox, gpointer d)
{
	GtkTreeIter iter;
	gchar* data = NULL;
	if (gtk_combo_box_get_active_iter (combobox, &iter))
	{
		GtkTreeModel* model = gtk_combo_box_get_model(combobox);
		gtk_tree_model_get (model, &iter, 0, &data, -1);
	}
	if(ProgName) g_free(ProgName);
	ProgName = g_strdup((gchar *)data);

	if(FrameOptions) gtk_widget_set_sensitive(FrameOptions, FALSE);

	if (!strcmp((gchar *)data,"a2ps") )
	{
		if(!FrameOptions) create_frame_options_a2ps(_("a2ps options"));
		else
		gtk_widget_set_sensitive(FrameOptions, TRUE);
		gtk_widget_set_sensitive(ButtonDisplay, TRUE);
	}
	else gtk_widget_set_sensitive(ButtonDisplay, FALSE);
}
