ca_file_create (const gchar *filename)
{
	gchar *sql = NULL;
	gchar *error = NULL;
        sqlite3 * ca_new_db = NULL;


        close(open(filename, O_CREAT, 0600));

	if (sqlite3_open (filename, &ca_new_db))
		return g_strdup_printf(_("Error opening filename '%s'"), filename) ;

	if (sqlite3_exec (ca_new_db, "BEGIN TRANSACTION;", NULL, NULL, &error))
		return error;

	if (sqlite3_exec (ca_new_db,
                          "CREATE TABLE db_properties (id INTEGER PRIMARY KEY, name TEXT, value TEXT, UNIQUE (name));",
                          NULL, NULL, &error)) {
		return error;
	}

	if (sqlite3_exec (ca_new_db,
                          "CREATE VIEW ca_properties AS SELECT id, name, value FROM db_properties;",
                          NULL, NULL, &error)) {
		return error;
	}

	if (sqlite3_exec (ca_new_db,
                          "CREATE TABLE certificates (id INTEGER PRIMARY KEY, is_ca BOOLEAN, serial TEXT, subject TEXT, "
			  "activation TIMESTAMP, expiration TIMESTAMP, revocation TIMESTAMP, pem TEXT, private_key_in_db BOOLEAN, "
			  "private_key TEXT, dn TEXT, parent_dn TEXT, parent_id INTEGER DEFAULT 0, parent_route TEXT, "
                          "expired_already_in_crl INTEGER, subject_key_id TEXT, issuer_key_id TEXT);",
                          NULL, NULL, &error)) {
		return error;
	}
	if (sqlite3_exec (ca_new_db,
                          "CREATE TABLE cert_requests (id INTEGER PRIMARY KEY, subject TEXT, pem TEXT, private_key_in_db BOOLEAN, "
			  "private_key TEXT, dn TEXT UNIQUE, parent_ca INTEGER);",
                          NULL, NULL, &error)) {
		return error;
	}

	if (sqlite3_exec (ca_new_db,
                          "CREATE TABLE ca_policies (id INTEGER PRIMARY KEY, ca_id INTEGER, name TEXT, value TEXT, UNIQUE (ca_id, name));",
                          NULL, NULL, &error)) {
		return error;
	}

	if (sqlite3_exec (ca_new_db,
                          "CREATE TABLE ca_crl (id INTEGER PRIMARY KEY, ca_id INTEGER, crl_version INTEGER, "
                          "date TIMESTAMP, UNIQUE (ca_id, crl_version));",
                          NULL, NULL, &error)) {
                fprintf (stderr, "%s\n", error);
		return error;
	}


	sql = sqlite3_mprintf ("INSERT INTO db_properties (id, name, value) VALUES (NULL, 'ca_db_version', %d);", CURRENT_GNOMINT_DB_VERSION);
	if (sqlite3_exec (ca_new_db, sql, NULL, NULL, &error))
		return error;
	sqlite3_free (sql);


        sql = sqlite3_mprintf ("INSERT INTO db_properties (id, name, value) VALUES (NULL, 'is_password_protected', '0');");

        if (sqlite3_exec (ca_new_db, sql, NULL, NULL, &error))
                return error;
        sqlite3_free (sql);

        sql = sqlite3_mprintf ("INSERT INTO db_properties (id, name, value) VALUES (NULL, 'hashed_password', '');");

        if (sqlite3_exec (ca_new_db, sql, NULL, NULL, &error))
                return error;

        sqlite3_free (sql);


	if (sqlite3_exec (ca_new_db, "COMMIT;", NULL, NULL, &error))
		return error;

        sqlite3_close (ca_new_db);

        ca_new_db = NULL;

        return NULL;
}
