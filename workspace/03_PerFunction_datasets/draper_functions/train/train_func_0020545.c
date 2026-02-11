main (int argc,
      char *argv[])
{
	GError *error = NULL;
	const gchar *password;
	GKeyFile *file;
	gboolean ret;
	gchar *contents;
	gsize length;

	g_set_prgname ("dump-keyring0-format");
	gcry_check_version (GCRYPT_VERSION);

	if (argc < 2 || argc > 3) {
		g_printerr ("usage: %s file.keyring [output]\n", g_get_prgname ());
		return 2;
	}

	if (!g_file_get_contents (argv[1], &contents, &length, &error)) {
		g_printerr ("%s: %s\n", g_get_prgname (), error->message);
		g_error_free (error);
		return 1;
	}

	file = g_key_file_new ();
	password = getpass ("Password: ");

	transform_keyring_binary_to_text (contents, length, password, file);
	g_free (contents);

	contents = g_key_file_to_data (file, &length, &error);
	g_key_file_free (file);

	if (contents == NULL) {
		g_printerr ("%s: couldn't encode: %s", g_get_prgname (), error->message);
		g_error_free (error);
		return 1;
	}

	ret = TRUE;
	if (argc == 3)
		ret = g_file_set_contents (argv[2], contents, length, &error);
	else
		g_print ("%s", contents);
	g_free (contents);

	if (!ret) {
		g_printerr ("%s: %s", g_get_prgname (), error->message);
		g_error_free (error);
		return 1;
	}

	return 0;
}
