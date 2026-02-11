pixbuf_file_chooser_set_current_filter (PixbufFileChooser *chooser, const gchar *extension)
{
	GdkPixbufFormat			*format;

	g_return_if_fail (extension != NULL);
	g_return_if_fail (PIXBUF_IS_FILE_CHOOSER (chooser));

	format = pixbuf_get_format_by_suffix (extension);

	if (format != NULL)
	{
		GtkWidget *combo = chooser->priv->combo_filter;

		if (combo != NULL)
		{
			GtkTreeModel 	*model;
			GtkTreeIter 	iter;
			gboolean		valid;
			model = gtk_combo_box_get_model (GTK_COMBO_BOX (combo));
			valid = gtk_tree_model_get_iter_first (model, &iter);
			while (valid)
		    {
			  	GtkFileFilter	*filter;
				GdkPixbufFormat	*it_format;
			  	gtk_tree_model_get (model, &iter,
					                FILTER_COL, &filter,
					                -1);
				it_format = g_object_get_data (G_OBJECT (filter), FILE_FORMAT_KEY);
				if (format == it_format)
				{
					gtk_combo_box_set_active_iter (GTK_COMBO_BOX (combo), &iter);
					valid = FALSE;
				}
				else
				{
					valid = gtk_tree_model_iter_next (model, &iter);
				}
			}
		}
    }
}
