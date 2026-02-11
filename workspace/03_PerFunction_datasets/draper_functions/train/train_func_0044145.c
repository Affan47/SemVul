ngc_get_ngcic_num(anbool is_ngc, int num) {
	int i, N;
	N = ngc_num_entries();
	for (i=0; i<N; i++) {
		ngc_entry* e = ngc_get_entry(i);
		if (e->is_ngc == is_ngc && e->id == num)
			return e;
	}
	return NULL;
}
