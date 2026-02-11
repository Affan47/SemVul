gtk_source_gutter_renderer_query_data (GtkSourceGutterRenderer      *renderer,
                                       GtkTextIter                  *start,
                                       GtkTextIter                  *end,
                                       GtkSourceGutterRendererState  state)
{
	g_return_if_fail (GTK_SOURCE_IS_GUTTER_RENDERER (renderer));
	g_return_if_fail (start != NULL);
	g_return_if_fail (end != NULL);

	g_signal_emit (renderer, signals[QUERY_DATA], 0, start, end, state);
}
