et_fiducial(
double x,
double y
) {
	if (et.nfid >= 4)
		error("et_fiducial: too many fiducial marks");
	et.fx[et.nfid] = x;
	et.fy[et.nfid] = et.height - y;
	et.nfid++;
}
