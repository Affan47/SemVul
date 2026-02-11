on_sourceview_hover_leave(gpointer data, GObject* where_the_data_was)
{
	Sourceview* sv = ANJUTA_SOURCEVIEW (data);

	if (sv->priv->tooltip_cell)
	{
		g_signal_emit_by_name (G_OBJECT (sv), "hover-leave", sv->priv->tooltip_cell);
		g_object_unref (sv->priv->tooltip_cell);
		sv->priv->tooltip_cell = NULL;
	}
	g_object_weak_unref (G_OBJECT(sv), on_sourceview_hover_destroy, where_the_data_was);
}
