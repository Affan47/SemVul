send_ignproc (const char *file, const char *dir)
{
    if (ign_inhibit_server || !supported_request ("Questionable"))
    {
	if (dir[0] != '\0')
	    (void) printf ("? %s/%s\n", dir, file);
	else
	    (void) printf ("? %s\n", file);
    }
    else
    {
	send_to_server ("Questionable ", 0);
	send_to_server (file, 0);
	send_to_server ("\012", 1);
    }
}
