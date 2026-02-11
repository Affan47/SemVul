GS_get_nozero(int id, int att, int *mode)
{
    geosurf *gs;

    G_debug(3, "GS_set_nozero");

    gs = gs_get_surf(id);

    if (gs) {
	if (att == ATT_TOPO) {
	    *mode = gs->nz_topo;
	}
	else if (att == ATT_COLOR) {
	    *mode = gs->nz_color;
	}
	else {
	    return (-1);
	}

	return (1);
    }

    return (-1);
}
