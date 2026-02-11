ofps_rem_vacc(ofps *s, vtx *vx) {


	if (vx->pn != NULL) {
		*vx->pn = vx->n;
		if (vx->n != NULL)
			vx->n->pn = vx->pn;
	}
	vx->pn = NULL;
	vx->n = NULL;
}
