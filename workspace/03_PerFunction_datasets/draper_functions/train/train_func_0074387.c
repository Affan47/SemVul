destroy_unref_source (gpointer source)
{
	if (!g_source_is_destroyed (source))
		g_source_destroy (source);
	g_source_unref (source);
}
