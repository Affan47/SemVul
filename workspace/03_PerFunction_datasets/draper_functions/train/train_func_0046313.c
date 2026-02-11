dump_channels (void)
{
    char    path[_POSIX_PATH_MAX];
    FILE   *fp;

    snprintf (path, sizeof (path), "%s/channels", Config_Dir);
    fp = fopen (path, "w");
    if (!fp)
    {
	logerr ("dump_channels", path);
	return;
    }
    fputs (":version 1", fp);
#ifdef WIN32
    fputc ('\r', fp);
#endif
    fputc ('\n', fp);
    hash_foreach (Channels, (hash_callback_t) dump_channel_cb, fp);
    if (fclose (fp))
	logerr ("dump_channels", "fclose");
}
