surf_draw_all_together(Nv_data * dc, Tcl_Interp * interp)
{
    int i, nsurfs;
    int sortSurfs[MAX_SURFS], sorti[MAX_SURFS];
    int *surf_list;
    float x, y, z;
    int num, w;


    num = 1;
    x = dc->light[num].x;
    y = dc->light[num].y;
    z = dc->light[num].z;
    w = dc->light[num].z;

    surf_list = GS_get_surf_list(&nsurfs);
    sort_surfs_max(surf_list, sortSurfs, sorti, nsurfs);
    G_free(surf_list);


    GS_setlight_position(num, x, y, z, w);
    num = 2;
    GS_setlight_position(num, 0., 0., 1., 0);

    for (i = 0; i < nsurfs; i++) {
	if (check_blank(interp, sortSurfs[i]) == 0) {
	    GS_draw_surf(sortSurfs[i]);
	}
    }


    for (i = 0; i < MAX_CPLANES; i++) {
	if (dc->Cp_on[i])
	    GS_draw_cplane_fence(sortSurfs[0], sortSurfs[1], i);
    }
    return (TCL_OK);
}
