pk_generate_pack_create_for_updates (PkServicePack *pack, const gchar *filename, gchar **excludes, GError **error)
{
	gboolean ret;
	PkGenpackHelper *helper;

	g_return_val_if_fail (error == NULL || *error == NULL, FALSE);


	helper = g_new0 (PkGenpackHelper, 1);
	helper->loop = g_main_loop_new (NULL, FALSE);
	helper->error = error;


	pk_service_pack_create_for_updates_async (pack, filename, excludes, cancellable,
						  (PkProgressCallback) pk_generate_pack_progress_cb, NULL,
						  (GAsyncReadyCallback) pk_generate_pack_generic_cb, helper);
	g_main_loop_run (helper->loop);

	ret = helper->ret;


	g_main_loop_unref (helper->loop);
	g_free (helper);

	return ret;
}
