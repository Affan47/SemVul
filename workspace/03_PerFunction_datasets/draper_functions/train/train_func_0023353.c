_dxftry_bin(struct parmlist *p)
{
    char *cp;


#ifndef DXD_OS_NON_UNIX
    if (strchr(p->filename, ':') != NULL)
	return IMPORT_STAT_FOUND;
#endif

    if ((cp = strrchr(p->filename, '.')) != NULL) {
	if (!strcmp(".bin", cp))
	    return IMPORT_STAT_FOUND;
    }

    return IMPORT_STAT_NOT_FOUND;
}
