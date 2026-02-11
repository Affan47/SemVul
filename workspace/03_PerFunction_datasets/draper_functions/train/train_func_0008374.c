brasero_tool_dialog_pack_options (BraseroToolDialog *self,
				  ...)
{
	gchar *title;
	va_list vlist;
	GtkWidget *child;
	GSList *list = NULL;
	BraseroToolDialogPrivate *priv;

	priv = BRASERO_TOOL_DIALOG_PRIVATE (self);

	va_start (vlist, self);
	while ((child = va_arg (vlist, GtkWidget *)))
		list = g_slist_prepend (list, child);
	va_end (vlist);

	title = g_strdup_printf ("<b>%s</b>", _("Options"));
	priv->options = brasero_utils_pack_properties_list (title, list);
	g_free (title);

	g_slist_free (list);

	gtk_widget_show_all (priv->options);
	gtk_box_pack_start (GTK_BOX (priv->upper_box),
			    priv->options,
			    FALSE,
			    FALSE,
			    0);
}
