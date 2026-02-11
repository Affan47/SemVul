Nviz_set_focus_map(int type, int id)
{
    if (GS_num_surfs() < 0 && GVL_num_vols() < 0) {
	GS_set_nofocus();
	return 0;
    }

    if (type == MAP_OBJ_UNDEFINED) {
	int *surf_list, num_surfs, *vol_list;

	if (GS_num_surfs() > 0) {
	    surf_list = GS_get_surf_list(&num_surfs);
	    id = surf_list[0];
	    G_free(surf_list);

	    GS_set_focus_center_map(id);
	}

	if (GVL_num_vols() > 0) {
	    vol_list = GVL_get_vol_list(&num_surfs);
	    id = vol_list[0];
	    G_free(vol_list);

	    GVL_set_focus_center_map(id);
	}
	return id;
    }

    if (type == MAP_OBJ_SURF) {
	GS_set_focus_center_map(id);
    }
    else if (type == MAP_OBJ_VOL) {
	GVL_set_focus_center_map(id);
    }

    return id;
}
