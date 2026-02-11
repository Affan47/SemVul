deinit_pollers() {

	struct poller *bp;
	int p;

	for (p = 0; p < nbpollers; p++) {
		bp = &pollers[p];

		if (bp && bp->pref)
			bp->term(bp);
	}
}
