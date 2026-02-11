load_settings(struct w *widgets)
{
    FILE *fp;
    long file_size;
    char *line;
    gchar *settings_file;


    gchar *old_settings_dir, *new_settings_dir, *cmd;


    settings_file = g_strdup_printf("%s/settings.conf", SETTINGS_DIR);


    old_settings_dir = g_strdup_printf("/etc/gbindadmin");
    new_settings_dir = g_strdup_printf("/etc/gadmin-bind");
    if( file_exists(old_settings_dir) && ! file_exists(new_settings_dir) )
    {
	cmd = g_strdup_printf("mv %s %s", old_settings_dir, new_settings_dir);
	if((fp=popen(cmd, "r"))==NULL)
	{
	}
	else
          pclose(fp);

	g_free(cmd);
    }
    g_free(old_settings_dir);
    g_free(new_settings_dir);


    if((fp=fopen(settings_file, "r"))==NULL)
    {

	g_free(settings_file);
        return;
    }
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);

    line = allocate(file_size+1);

    if( file_size > 1 )
    while(fgets(line, file_size, fp)!=NULL)
    {
	if( strlen(line) > 1000 )
	  continue;

	if( strstr(line, "chroot_directory:") )
	  sscanf(line, "%*s %s", CHROOT_PATH_BUF);

	if( strstr(line, "syslog_file_path:") )
	  sscanf(line, "%*s %s", SYSLOG_PATH_BUF);

	if( strstr(line, "resolv_conf_path:") )
	  sscanf(line, "%*s %s", RESOLV_PATH_BUF);
    }
    fclose(fp);
    free(line);
    g_free(settings_file);
}
