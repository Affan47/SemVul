gkd_ssh_agent_uninitialize (void)
{
	gboolean ret;

	g_assert (pkcs11_main_mutex);
	ret = g_mutex_trylock (pkcs11_main_mutex);
	g_assert (ret);

		g_assert (GCK_IS_SESSION (pkcs11_main_session));
		g_assert (!pkcs11_main_checked);
		g_object_unref (pkcs11_main_session);
		pkcs11_main_session = NULL;

	g_mutex_unlock (pkcs11_main_mutex);
	g_mutex_clear (pkcs11_main_mutex);
	g_free (pkcs11_main_mutex);
	g_cond_clear (pkcs11_main_cond);
	g_free (pkcs11_main_cond);

	gck_list_unref_free (pkcs11_modules);
	pkcs11_modules = NULL;
}
