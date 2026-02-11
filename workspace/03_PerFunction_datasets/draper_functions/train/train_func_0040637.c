ipol(int xp, int yp) {
	double x = xp * m_SX;
	double y = yp * m_SY;
	int i = (int)floor(x);
	int j = (int)floor(y);
	double dx = x - i;
	double dy = y - j;
	double value = 0;
	for (int m = -1; m <= 2; m++) {
		int xo = i + m;
		double rx = R(m-dx);
		for (int n = -1; n <= 2; n++) {
			int yo = j + n;
			value += m_Data->getValue(xo, yo) * rx * R(dy-n);
		}
	}
	return value;
}
