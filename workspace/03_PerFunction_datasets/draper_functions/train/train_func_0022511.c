run(char *pgm, char *flags, char *name)
{
    char path[GPATH_MAX];
    int stat;

    sprintf(path, "%s/etc/mon.%s", G_gisbase(), pgm);

    if (*flags) {
	if ((stat = G_spawn(path, pgm, flags, name, NULL)))
	    G_sleep(3);
    }
    else {
	if ((stat = G_spawn(path, pgm, name, NULL)))
	    G_sleep(3);
    }

    return stat;
}
