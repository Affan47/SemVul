preview_pane_dispose (GObject *object)
{
	EPreviewPanePrivate *priv;

	priv = E_PREVIEW_PANE_GET_PRIVATE (object);

	if (priv->web_view_new_activity_handler_id > 0) {
		g_signal_handler_disconnect (
			priv->web_view,
			priv->web_view_new_activity_handler_id);
		priv->web_view_new_activity_handler_id = 0;
	}

	g_clear_object (&priv->alert_bar);
	g_clear_object (&priv->search_bar);
	g_clear_object (&priv->web_view);


	G_OBJECT_CLASS (e_preview_pane_parent_class)->dispose (object);
}
