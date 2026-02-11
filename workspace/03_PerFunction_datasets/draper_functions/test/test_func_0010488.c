GP_site_exists(int id)
{
    int i, found = 0;

    if (NULL == gp_get_site(id)) {
	return (0);
    }

    for (i = 0; i < Next_site && !found; i++) {
	if (Site_ID[i] == id) {
	    found = 1;
	}
    }

    G_debug(3, "GP_site_exists(): found=%d", found);

    return (found);
}
