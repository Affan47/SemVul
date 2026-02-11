GP_unselect_surf(int hp, int hs)
{
    geosite *gp;
    int i, j;

    if (!GP_surf_is_selected(hp, hs)) {
	return (1);
    }

    gp = gp_get_site(hp);

    if (gp) {
	for (i = 0; i < gp->n_surfs; i++) {
	    if (gp->drape_surf_id[i] == hs) {
		for (j = i; j < gp->n_surfs - 1; j++) {
		    gp->drape_surf_id[j] = gp->drape_surf_id[j + 1];
		}

		gp->n_surfs -= 1;
		return (1);
	    }
	}
    }

    return (-1);
}
