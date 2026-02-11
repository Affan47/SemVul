GP_set_zmode(int id, int use_z)
{
    geosite *gp;

    if (NULL == (gp = gp_get_site(id))) {
	return (-1);
    }

    if (use_z) {
	if (gp->has_z) {
	    gp->use_z = 1;
	    return (1);
	}

	return (0);
    }

    gp->use_z = 0;
    return (1);
}
