t1_getwmsedec(
		int nmsedec,
		int compno,
		int level,
		int orient,
		int bpno,
		int qmfbid,
		double stepsize,
		int numcomps,
		int mct)
{
	double w1, w2, wmsedec;
	if (qmfbid == 1) {
		w1 = (mct && numcomps==3) ? mct_getnorm(compno) : 1.0;
		w2 = dwt_getnorm(level, orient);
	} else {
		w1 = (mct && numcomps==3) ? mct_getnorm_real(compno) : 1.0;
		w2 = dwt_getnorm_real(level, orient);
	}
	wmsedec = w1 * w2 * stepsize * (1 << bpno);
	wmsedec *= wmsedec * nmsedec / 8192.0;

	return wmsedec;
}
