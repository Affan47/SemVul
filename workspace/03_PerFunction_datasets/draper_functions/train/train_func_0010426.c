fopen_histogram_new(const char *name)
{
    FILE *fd;

    fd = G_fopen_new_misc("cell_misc", "histogram", name);
    if (fd == NULL)
	G_warning(_("can't create histogram for [%s in %s]"), name,
		  G_mapset());

    return fd;
}
