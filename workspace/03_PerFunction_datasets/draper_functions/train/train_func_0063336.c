source_registry_server_any_true (GSignalInvocationHint *ihint,
                                 GValue *return_accu,
                                 const GValue *handler_return,
                                 gpointer unused)
{
	if (g_value_get_boolean (handler_return))
		g_value_set_boolean (return_accu, TRUE);

	return TRUE;
}
