userdb_dump (void)
{
    FILE   *fp;
    char    path[_POSIX_PATH_MAX], tmppath[_POSIX_PATH_MAX];

    log_message ("userdb_dump: dumping user database");
    snprintf (tmppath, sizeof (tmppath), "%s/users.tmp", Config_Dir);
    fp = fopen (tmppath, "w");
    if (!fp)
    {
	logerr ("userdb_dump", tmppath);
	return -1;
    }
#ifdef WIN32
    fputs (":version 1\r\n", fp);
#else
    fputs (":version 1\n", fp);
#endif
    hash_foreach (User_Db, (hash_callback_t) dump_userdb, fp);
    if (fflush (fp))
    {
	logerr ("userdb_dump", "fflush");
	fclose (fp);
	return -1;
    }
    if (fclose (fp))
    {
	logerr ("userdb_dump", "fclose");
	return -1;
    }
    snprintf (path, sizeof (path), "%s/users", Config_Dir);
    if (unlink (path))
	logerr ("userdb_dump", "unlink");
    if (rename (tmppath, path))
    {
	logerr ("userdb_dump", "rename");
	return -1;
    }
    log_message ("userdb_dump: wrote %d entries", User_Db->dbsize);
    return 0;
}
