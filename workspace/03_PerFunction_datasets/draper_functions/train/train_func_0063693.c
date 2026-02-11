ao_toolbar_update(AoDocList *self)
{
	AoDocListPrivate *priv = AO_DOC_LIST_GET_PRIVATE(self);


	if (! priv->enable_doclist)
	{
		if (priv->toolbar_doclist_button != NULL)
		{
			gtk_widget_hide(GTK_WIDGET(priv->toolbar_doclist_button));
		}
	}
	else
	{
		if (priv->toolbar_doclist_button == NULL)
		{
			priv->toolbar_doclist_button = gtk_tool_button_new_from_stock(GTK_STOCK_INDEX);
#if GTK_CHECK_VERSION(2, 12, 0)
			gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(priv->toolbar_doclist_button),
				_("Show Document List"));
#endif
			plugin_add_toolbar_item(geany_plugin, priv->toolbar_doclist_button);
			ui_add_document_sensitive(GTK_WIDGET(priv->toolbar_doclist_button));

			g_signal_connect(priv->toolbar_doclist_button, "clicked",
				G_CALLBACK(ao_toolbar_item_doclist_clicked_cb), self);
		}
		gtk_widget_show(GTK_WIDGET(priv->toolbar_doclist_button));
	}
}
