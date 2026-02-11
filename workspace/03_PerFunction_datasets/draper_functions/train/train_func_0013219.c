del_vtx1(ofps *s, vtx *vx) {
	node *nn, *nnn;

	if (vx->plp != NULL) {
		*vx->plp = vx->link;
		if (vx->link != NULL)
			vx->link->plp = vx->plp;
		s->nv--;
	}

	if (vx->pfchl != NULL) {
		*vx->pfchl = vx->fchl;
		if (vx->fchl != NULL)
			vx->fchl->pfchl = vx->pfchl;
	}
	vx->pfchl = NULL;
	vx->fchl = NULL;

	if (vx->ofake == 0) {


		vtx_cache_rem(s, vx);


		ofps_rem_vacc(s, vx);


		ofps_rem_vseed(s, vx);
	}


	if (vx->psvtxs != NULL) {
		*vx->psvtxs = NULL;
		vx->psvtxs = NULL;
	}
}
