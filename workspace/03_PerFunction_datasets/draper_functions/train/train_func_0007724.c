paste_callback (gpointer target)
{
	g_assert (target != NULL);

	g_signal_emit_by_name (target, "paste-clipboard");
}
