gvl_isosurf_freemem(geovol_isosurf * isosurf)
{
    int i;

    G_debug(5, "gvl_isosurf_freemem");

    if (!isosurf)
	return (-1);

    for (i = 0; i < MAX_ATTS; i++) {
	gvl_isosurf_set_att_src(isosurf, i, NOTSET_ATT);
    }

    G_free(isosurf->data);

    return (1);
}
