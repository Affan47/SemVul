getDistp(double t) {
	GLEPoint T;
	getCp(t, T);
	return T.norm();
}
