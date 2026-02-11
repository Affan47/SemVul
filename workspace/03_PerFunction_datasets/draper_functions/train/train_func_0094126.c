G_get_reclass(const char *name, const char *mapset,
		  struct Reclass *reclass)
{
    FILE *fd;
    int stat;

    fd = fopen_cellhd_old(name, mapset);
    if (fd == NULL)
	return -1;
    reclass->name = NULL;
    reclass->mapset = NULL;
    reclass->type = reclass_type(fd, &reclass->name, &reclass->mapset);
    if (reclass->type <= 0) {
	fclose(fd);
	return reclass->type;
    }

    switch (reclass->type) {
    case RECLASS_TABLE:
	stat = get_reclass_table(fd, reclass);
	break;
    default:
	stat = -1;
    }

    fclose(fd);
    if (stat < 0) {
	if (stat == -2)
	    G_warning(_("Too many reclass categories for [%s in %s]"),
		      name, mapset);
	else
	    G_warning(_("Illegal reclass format in header file for [%s in %s]"),
		      name, mapset);
	stat = -1;
    }
    return stat;
}
