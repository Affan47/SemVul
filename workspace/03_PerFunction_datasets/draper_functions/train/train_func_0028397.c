write_env(int loc)
{
    FILE *fd;
    int n;
    char dummy[2];
    void (*sigint) ()
#ifdef SIGQUIT
     , (*sigquit) ()
#endif
     ;

    if (loc == G_VAR_GISRC && varmode == G_GISRC_MODE_MEMORY)
	return 0;


    sigint = signal(SIGINT, SIG_IGN);
#ifdef SIGQUIT
    sigquit = signal(SIGQUIT, SIG_IGN);
#endif
    if ((fd = open_env("w", loc))) {
	for (n = 0; n < count; n++)
	    if (env[n].name && env[n].value && env[n].loc == loc
		&& (sscanf(env[n].value, "%1s", dummy) == 1))
		fprintf(fd, "%s: %s\n", env[n].name, env[n].value);
	fclose(fd);
    }

    signal(SIGINT, sigint);
#ifdef SIGQUIT
    signal(SIGQUIT, sigquit);
#endif

    return 0;
}
