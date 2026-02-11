debugger_set_thread_finish (Debugger *debugger, const GDBMIValue *mi_results, const GList *cli_results, GError *error)
{
	const GDBMIValue *literal;
	guint id;

	if (mi_results == NULL) return;

	literal = gdbmi_value_hash_lookup (mi_results, "new-thread-id");
	if (literal == NULL) return;

	id = strtoul (gdbmi_value_literal_get (literal), NULL, 10);
	if (id == 0) return;

	debugger->priv->current_thread = id;
	g_signal_emit_by_name (debugger->priv->instance, "frame-changed", 0, debugger->priv->current_thread);

	return;
}
