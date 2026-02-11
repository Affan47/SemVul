ifp_treewalk_close(void * tws_p) {
	struct treewalk_state * tws = tws_p;
	int i = 0;


	while (tws->q) {
		int a1, a2;
		int e;
		e = dequeue_dentry(&tws->q, tws->rp, tws->rn, &a1, &a2);
		if (e <= 0) {
			ifp_err_i(e, "problem cleaning up");
			if (i == 0) {
				i = e;
			}
		}
	}
	free(tws);
	tws = tws_p = NULL;

	return i;
}
