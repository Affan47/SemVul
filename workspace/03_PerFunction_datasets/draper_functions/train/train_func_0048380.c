gvld_vol(geovol *gvl)
{
    G_debug(5, "gvld_vol(): id=%d", gvl->gvol_id);


    if (0 > gvl_slices_calc(gvl))
	return (-1);

    if (0 > gvld_slices(gvl))
	return (-1);


    if (0 > gvl_isosurf_calc(gvl))
	return (-1);

    if (0 > gvld_isosurf(gvl))
	return (-1);

    return (1);
}
