distToParamValue(double t1, double dist) {
	GLEPoint T;
	getCp(t1, T);
	double dist_corr = dist * 1.05;
	double t = t1 + dist_corr / T.norm();
	return distToParamValue(t1, dist, t);
}
