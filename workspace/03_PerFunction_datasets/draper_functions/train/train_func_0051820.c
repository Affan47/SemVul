gkd_gpg_agent_initialize_with_module (GckModule *module)
{
	GckSession *session = NULL;
	GckSlot *slot;
	GError *error = NULL;
	GList *modules;

	g_assert (GCK_IS_MODULE (module));


	modules = g_list_append (NULL, module);
	slot = gck_modules_token_for_uri (modules, "pkcs11:token=Secret%20Store", &error);
	g_list_free (modules);

	if (!slot) {
		g_warning ("couldn't find secret store module: %s", egg_error_message (error));
		g_clear_error (&error);
		return FALSE;
	}


	session = gck_slot_open_session (slot, GCK_SESSION_READ_WRITE | GCK_SESSION_AUTHENTICATE, NULL, &error);
	g_object_unref (slot);

	if (!session) {
		g_warning ("couldn't select a usable pkcs#11 slot for the gpg agent to use");
		g_clear_error (&error);
		return FALSE;
	}

	pkcs11_module = g_object_ref (module);

	pkcs11_main_mutex = g_new0 (GMutex, 1);
	g_mutex_init (pkcs11_main_mutex);
	pkcs11_main_cond = g_new0 (GCond, 1);
	g_cond_init (pkcs11_main_cond);
	pkcs11_main_checked = FALSE;
	pkcs11_main_session = session;

	cache_settings = g_settings_new ("org.gnome.crypto.cache");

	return TRUE;
}
