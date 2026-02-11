io_loading_error_info_bar_response (GtkWidget *info_bar,
				    gint       response_id,
				    GeditTab  *tab)
{
	GeditDocument *doc;
	GeditView *view;
	GFile *location;
	const GeditEncoding *encoding;

	doc = gedit_tab_get_document (tab);
	g_return_if_fail (GEDIT_IS_DOCUMENT (doc));

	view = gedit_tab_get_view (tab);
	g_return_if_fail (GEDIT_IS_VIEW (view));

	location = gedit_document_get_location (doc);

	switch (response_id)
	{
		case GTK_RESPONSE_OK:
			g_return_if_fail (location != NULL);

			encoding = gedit_conversion_error_info_bar_get_encoding (
					GTK_WIDGET (info_bar));

			if (encoding != NULL)
			{
				tab->priv->tmp_encoding = encoding;
			}

			set_info_bar (tab, NULL);
			gedit_tab_set_state (tab, GEDIT_TAB_STATE_LOADING);

			g_return_if_fail (tab->priv->auto_save_timeout <= 0);

			gedit_document_load (doc,
					     location,
					     tab->priv->tmp_encoding,
					     tab->priv->tmp_line_pos,
					     tab->priv->tmp_column_pos,
					     FALSE);
			break;
		case GTK_RESPONSE_YES:

			tab->priv->not_editable = FALSE;
			gtk_text_view_set_editable (GTK_TEXT_VIEW (view),
			                            TRUE);
			set_info_bar (tab, NULL);
			break;
		default:
			if (location != NULL)
			{
				_gedit_recent_remove (GEDIT_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (tab))), location);
			}

			remove_tab (tab);
			break;
	}

	if (location != NULL)
	{
		g_object_unref (location);
	}
}
