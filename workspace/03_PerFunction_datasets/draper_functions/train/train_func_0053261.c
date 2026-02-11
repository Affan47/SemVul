_gtk_source_engine_set_style_scheme (GtkSourceEngine      *engine,
				     GtkSourceStyleScheme *scheme)
{
	g_return_if_fail (GTK_SOURCE_IS_ENGINE (engine));
	g_return_if_fail (GTK_SOURCE_IS_STYLE_SCHEME (scheme) || scheme == NULL);
	g_return_if_fail (GTK_SOURCE_ENGINE_GET_INTERFACE (engine)->set_style_scheme != NULL);

	GTK_SOURCE_ENGINE_GET_INTERFACE (engine)->set_style_scheme (engine, scheme);
}
