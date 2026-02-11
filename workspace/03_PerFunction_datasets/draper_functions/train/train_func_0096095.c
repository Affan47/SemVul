brasero_burn_options_add_source (BraseroBurnOptions *self,
				 const gchar *title,
				 ...)
{
	va_list vlist;
	GtkWidget *child;
	GSList *list = NULL;
	BraseroBurnOptionsPrivate *priv;

	priv = BRASERO_BURN_OPTIONS_PRIVATE (self);


	priv->message_input = brasero_notify_new ();
	list = g_slist_prepend (list, priv->message_input);

	va_start (vlist, title);
	while ((child = va_arg (vlist, GtkWidget *))) {
		GtkWidget *hbox;
		GtkWidget *alignment;

		hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 12);
		gtk_widget_show (hbox);

		gtk_box_pack_start (GTK_BOX (hbox), child, TRUE, TRUE, 0);

		alignment = gtk_alignment_new (0.0, 0.5, 0., 0.);
		gtk_widget_show (alignment);
		gtk_size_group_add_widget (priv->size_group, alignment);
		gtk_box_pack_start (GTK_BOX (hbox), alignment, FALSE, FALSE, 0);

		list = g_slist_prepend (list, hbox);
	}
	va_end (vlist);

	priv->source = brasero_utils_pack_properties_list (title, list);
	g_slist_free (list);

	gtk_container_add (GTK_CONTAINER (priv->source_placeholder), priv->source);
	gtk_widget_show (priv->source_placeholder);
}
