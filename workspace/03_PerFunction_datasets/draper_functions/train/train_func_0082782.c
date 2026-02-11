cd_client_import_free_helper (CdClientImportHelper *helper)
{
	g_object_unref (helper->file);
	g_object_unref (helper->dest);
	if (helper->cancellable != NULL)
		g_object_unref (helper->cancellable);
	if (helper->profile_added_id > 0)
		g_signal_handler_disconnect (helper->client, helper->profile_added_id);
	if (helper->hangcheck_id > 0)
		g_source_remove (helper->hangcheck_id);
	g_object_unref (helper->client);
	g_object_unref (helper->res);
	g_free (helper);
}
