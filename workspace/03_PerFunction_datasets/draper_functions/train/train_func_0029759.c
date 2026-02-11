GP_set_trans(int id, float xtrans, float ytrans, float ztrans)
{
    geosite *gp;

    G_debug(3, "GP_set_trans(): id=%d trans=%f,%f,%f",
	    id, xtrans, ytrans, ztrans);

    gp = gp_get_site(id);
    if (gp) {
	gp->x_trans = xtrans;
	gp->y_trans = ytrans;
	gp->z_trans = ztrans;
    }

    return;
}
