update_label_regex_error (TestSearch *search)
{
	GError *error;

	error = gtk_source_search_context_get_regex_error (search->priv->search_context);

	if (error == NULL)
	{
		gtk_label_set_text (search->priv->label_regex_error, "");
		gtk_widget_hide (GTK_WIDGET (search->priv->label_regex_error));
	}
	else
	{
		gtk_label_set_text (search->priv->label_regex_error, error->message);
		gtk_widget_show (GTK_WIDGET (search->priv->label_regex_error));
		g_error_free (error);
	}
}
