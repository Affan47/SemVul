patch_location_order(
	alphix *saix,
	alphix *paix,
	int ixord,
	char *_ax
) {
	char *ax;
	char *v;
	alphix *rh;
	alphix *lh;
	int ri, li;

	if ((ax = malloc(strlen(_ax)+1)) == NULL)
		return -1;
	strcpy(ax,_ax);

	if (ixord == 0) {
		lh = saix;
		rh = paix;
	} else {
		rh = saix;
		lh = paix;
	}


	v = find_start(rh, ax);

	ri = rh->nix(rh, v);
	*v = '\000';
	li = lh->nix(lh, ax);
	free(ax);
	if (ri < 0 || li < 0)
		return -1;

	if (ixord == 0)
		return li * rh->cmct + ri;
	else
		return ri * lh->cmct + li;
}
