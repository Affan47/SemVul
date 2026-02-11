run_local_command(gchar *outfile,gchar *errfile,gchar* command,gboolean under)
{
	gchar *temp;
	gint ierr = 0;

	unlink (outfile);
	unlink (errfile);

	if(under)
	{
#ifdef G_OS_WIN32
		temp = g_strdup_printf("%s >%s 2>%s ",command, outfile, errfile);
		createProcessWin32(temp);

#else
		if(strstr(command,">"))
 		temp = g_strdup_printf("sh -c '%s 2>%s&'",command, errfile);
		else
 		temp = g_strdup_printf("sh -c '%s >%s 2>%s&'",command, outfile, errfile);
		ierr = system(temp);
#endif

		Waiting(0.5);
	}
	else
	{
#ifdef G_OS_WIN32
		temp = g_strdup_printf("%s >%s 2>%s",command,outfile,errfile);
#else
 		temp = g_strdup_printf("sh -c '%s >%s 2>%s'",command,outfile,errfile);
#endif
 		ierr = system(temp);
	}

	g_free(temp);
}
