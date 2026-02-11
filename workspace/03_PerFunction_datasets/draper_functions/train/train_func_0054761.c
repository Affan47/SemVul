build_cancel_command (BasicAutotoolsPlugin* bplugin, BuildContext *context,
					  GError **err)
{
	GList *node;

	if (context == NULL) return;

	for (node = g_list_first (bplugin->contexts_pool); node != NULL; node = g_list_next (node))
	{
		if (node->data == context)
		{
			build_context_cancel (context);
			return;
		}
	}


	g_return_if_reached ();
}
