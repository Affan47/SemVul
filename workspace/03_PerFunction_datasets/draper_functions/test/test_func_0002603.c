GP_attmode_color(int id, const char *filename)
{
    geosite *gp;

    if (NULL == (gp = gp_get_site(id))) {
	return (-1);
    }

    if (!gp->has_att) {
	return (0);
    }

    if (Gp_set_color(filename, gp->points)) {
	gp->attr_mode = ST_ATT_COLOR;
	return (1);
    }

    return (-1);
}
