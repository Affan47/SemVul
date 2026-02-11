batch_push(int nreg, double delay) {
	int k;
	batch_copyregion(batch_reg, batch_dxs, batch_dys, nreg, delay);

	fb_push();
	for (k=0; k < nreg; k++) {
		sraRgnDestroy(batch_reg[k]);
	}
}
