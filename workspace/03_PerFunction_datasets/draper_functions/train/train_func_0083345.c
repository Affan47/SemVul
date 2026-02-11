jabber_gpg_changed(session_t *s, const char *name) {
	plugin_t *gpg_plug;
	const char *key;
	const char *passhrase;

	char *error;
	char *msg;

	if (!session_postinit) return;


	session_int_set(s, "__gpg_enabled", 0);
	if (session_int_get(s, "gpg_active") != 1) return;

	if (!(key = session_get(s, "gpg_key")) || !(passhrase = session_get(s, "gpg_password"))) {
		print("jabber_gpg_config", session_name(s));
		return;
	}

	if (!(gpg_plug = plugin_find("gpg"))) {
		print("jabber_gpg_plugin", session_name(s));
		return;
	}

	msg = xstrdup("test");
	msg = jabber_openpgp(s, NULL, JABBER_OPENGPG_SIGN, msg, NULL, &error);

	if (error) {
		session_set(s, "gpg_active", "0");
		session_set(s, "gpg_password", NULL);
		print("jabber_gpg_fail", session_name(s), key, error);
		xfree(error);
	} else	{
		session_int_set(s, "__gpg_enabled", 1);
		print("jabber_gpg_ok", session_name(s), key);
	}
	jabber_write_status(s);
	xfree(msg);
}
