_secret_sync_new (void)
{
	SecretSync *sync;

	sync = g_new0 (SecretSync, 1);

	sync->context = g_main_context_new ();
	sync->loop = g_main_loop_new (sync->context, FALSE);

	return sync;
}
