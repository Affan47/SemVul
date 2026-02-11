gv_update_drapesurfs(void)
{
    geovect *gv;
    int i, j;

    for (gv = Vect_top; gv; gv = gv->next) {
	if (gv->n_surfs) {
	    for (i = 0; i < gv->n_surfs; i++) {
		if (gv->drape_surf_id[i]) {
		    if (NULL == gs_get_surf(gv->drape_surf_id[i])) {
			for (j = i; j < gv->n_surfs - 1; j++) {
			    gv->drape_surf_id[j] = gv->drape_surf_id[j + 1];
			}

			gv->n_surfs = gv->n_surfs - 1;
		    }
		}
	    }
	}
    }
}
