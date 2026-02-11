site_highlight_get_geosite(char *name)
{
    geosite *gp;
    int i, n, *id;

    id = GP_get_site_list(&n);
    for (i = 0; i < n; i++) {
	gp = gp_get_site(id[i]);
	if (!strcmp(gp->filename, name)) {
	    free(id);
	    return gp;
	}
    }
    free(id);
    return NULL;
}
