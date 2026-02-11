dsv_readint(int *v) {
	int r;
	r = dsv_nextfield();
	if(r != DSV_OK) return r;
	*v = atoi(dsv_cfield);
	return DSV_OK;
}
