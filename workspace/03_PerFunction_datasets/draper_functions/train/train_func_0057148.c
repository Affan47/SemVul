test_lock_db (TestArgs *args)
{
    const gchar *basedir;
    gchar *filename;
    gint ms;

    ms = atoi(args->argv[0]);
    lock_file = open(args->argv[1], O_RDWR | O_APPEND);

    basedir = g_getenv ("ACCOUNTS");
    if (G_LIKELY (!basedir))
        basedir = g_get_home_dir ();
    filename = g_build_filename (basedir, "accounts.db", NULL);
    sqlite3_open (filename, &sqldb);
    g_free (filename);

    lock_db(TRUE);

    g_timeout_add (ms, (GSourceFunc)unlock_and_exit, NULL);

    return FALSE;
}
