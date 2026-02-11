bstrListDestroy (struct bstrList * sl) {
int i;
	if (sl == NULL || sl->qty < 0) return BSTR_ERR;
	for (i=0; i < sl->qty; i++) {
		if (sl->entry[i]) {
			bdestroy (sl->entry[i]);
			sl->entry[i] = NULL;
		}
	}
	sl->qty  = -1;
	sl->mlen = -1;
	bstr__free (sl->entry);
	sl->entry = NULL;
	bstr__free (sl);
	return BSTR_OK;
}
