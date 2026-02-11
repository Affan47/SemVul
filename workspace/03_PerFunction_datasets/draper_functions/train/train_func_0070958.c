G_convert_dirseps_from_host(char *path)
{
    char *i;

    for (i = path; *i; i++) {
	if (*i == HOST_DIRSEP)
	    *i = GRASS_DIRSEP;
    }

    return path;
}
