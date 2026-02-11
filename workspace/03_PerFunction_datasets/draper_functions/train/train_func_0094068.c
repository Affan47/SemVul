gtk_source_context_engine_text_deleted (GtkSourceEngine *engine,
					gint             offset,
					gint             length)
{
	GtkSourceContextEngine *ce = GTK_SOURCE_CONTEXT_ENGINE (engine);

	g_return_if_fail (length > 0);

	if (!ce->priv->disabled)
	{
		invalidate_region (ce, offset, - length);
	}
}
