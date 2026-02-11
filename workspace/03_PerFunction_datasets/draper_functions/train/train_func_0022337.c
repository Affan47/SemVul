__ca_file_password_protect_cb (void *pArg, int argc, char **argv, char **columnNames)
{
	CaFilePwdChange * pwd_change = (CaFilePwdChange *) pArg;
	const gchar *table = pwd_change->table;
	const gchar *pwd = pwd_change->new_password;
	gchar *error;
	gchar *sql;
	gchar *new_pkey;

	if (atoi(argv[1]) == 0)
		return 0;

	new_pkey = pkey_manage_crypt_w_pwd (argv[2], argv[3], pwd);

        sql = sqlite3_mprintf ("UPDATE %q SET private_key='%q' WHERE id='%q';",
                               table, new_pkey, argv[0]);

	if (sqlite3_exec (ca_db, sql, NULL, NULL, &error)) {
		fprintf (stderr, "Error while executing: %s. %s", sql, error);
		sqlite3_exec (ca_db, "ROLLBACK;", NULL, NULL, &error);
		sqlite3_free (sql);
		g_free (new_pkey);
		return 1;
	}

	sqlite3_free(sql);

	g_free (new_pkey);

	return 0;
}
