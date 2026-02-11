scp_put_file(char* fout,char* ferr,
			 char* filename,char* localdir,char* remotedir,
			 char *hostname,char *username,char* password)
{
	gchar *command;
	gchar* message;

	message = g_strdup_printf( _("Put %s/%s file at %s host..."),
					remotedir,filename,hostname
				);


	show_progress_connection();
	progress_connection(0,message,FALSE);

	command = g_strdup_printf(
					"sh -c \"sh -c 'scp %s/%s %s@%s:%s/%s' >%s 2>%s\"",
					localdir,filename,username,hostname,remotedir,filename,
					fout,ferr);
	unlink(fout);
	unlink(ferr);
	if(system(command)==0)
	{
		g_free(command);
		hide_progress_connection();
		progress_connection(0," ",TRUE);
	}
	else
	{
		g_free(command);
		return 1;
	}

	return 0;
}
