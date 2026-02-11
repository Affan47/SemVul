pk_console_transaction_cb (PkTransactionPast *item, gpointer user_data)
{
	struct passwd *pw;
	const gchar *role_text;
	gchar **lines;
	gchar **parts;
	guint i, lines_len;
	gchar *package = NULL;
	gchar *tid;
	gchar *timespec;
	gboolean succeeded;
	guint duration;
	gchar *cmdline;
	guint uid;
	gchar *data;
	PkRoleEnum role;


	g_object_get (item,
		      "role", &role,
		      "tid", &tid,
		      "timespec", &timespec,
		      "succeeded", &succeeded,
		      "duration", &duration,
		      "cmdline", &cmdline,
		      "uid", &uid,
		      "data", &data,
		      NULL);

	role_text = pk_role_enum_to_string (role);

	g_print ("%s: %s\n", _("Transaction"), tid);

	g_print (" %s: %s\n", _("System time"), timespec);

	g_print (" %s: %s\n", _("Succeeded"), succeeded ? _("True") : _("False"));

	g_print (" %s: %s\n", _("Role"), role_text);


	if (duration > 0) {

		g_print (" %s: %i %s\n", _("Duration"), duration, _("(seconds)"));
	}


	g_print (" %s: %s\n", _("Command line"), cmdline);

	g_print (" %s: %i\n", _("User ID"), uid);


	pw = getpwuid (uid);
	if (pw != NULL) {
		if (pw->pw_name != NULL) {

			g_print (" %s: %s\n", _("Username"), pw->pw_name);
		}
		if (pw->pw_gecos != NULL) {

			g_print (" %s: %s\n", _("Real name"), pw->pw_gecos);
		}
	}


	lines = g_strsplit (data, "\n", -1);
	lines_len = g_strv_length (lines);
	if (lines_len > 0)
		g_print (" %s\n", _("Affected packages:"));
	else
		g_print (" %s\n", _("Affected packages: None"));
	for (i=0; i<lines_len; i++) {
		parts = g_strsplit (lines[i], "\t", 3);


		package = pk_package_id_to_printable (parts[1]);
		g_print (" - %s %s\n", parts[0], package);
		g_free (package);
		g_strfreev (parts);
	}
	g_free (tid);
	g_free (timespec);
	g_free (cmdline);
	g_free (data);
	g_strfreev (lines);
}
