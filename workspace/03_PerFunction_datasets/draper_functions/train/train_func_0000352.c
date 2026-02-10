set_visible (GtkSourceGutterRenderer *renderer,
             gboolean                 visible)
{
	visible = visible != FALSE;

	if (renderer->priv->visible != visible)
	{
		renderer->priv->visible = visible;
		g_object_notify (G_OBJECT (renderer), "visible");

		gtk_source_gutter_renderer_queue_draw (renderer);
	}
}
