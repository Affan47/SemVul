throughPoint(GLEPoint& p, GLEPoint& dir1, GLEPoint& dir2) {
	double poly[6];
	double a = p.getX() - m_P0.getX();
	double b = 3*(m_P0.getX()-m_P3.getX());
	double c = 2*(m_P3.getX()-m_P0.getX());
	double d = dir1.getX();
	double e = dir2.getX() - 2*dir1.getX();
	double f = dir1.getX() - dir2.getX();
	double g = p.getY() - m_P0.getY();
	double h = 3*(m_P0.getY()-m_P3.getY());
	double i = 2*(m_P3.getY()-m_P0.getY());
	double j = dir1.getY();
	double k = dir2.getY() - 2*dir1.getY();
	double l = dir1.getY() - dir2.getY();
	poly[5] = c*l - i*f;
	poly[4] = c*k + b*l - i*e - h*f;
	poly[3] = c*j + b*k - i*d - h*e;
	poly[2] = b*j + a*l - h*d - g*f;
	poly[1] = a*k - g*e;
	poly[0] = a*j - g*d;
	GLEPolynomial polynomial(poly, 5);
	polynomial.horner(1);

	double t = polynomial.newtonRaphson(0.5);
	double scale = (a + b*t*t + c*t*t*t)/(d + e*t + f*t*t)/(3*t);
	m_P1.set(m_P0);
	m_P1.add(scale, dir1);
	m_P2.set(m_P3);
	m_P2.add(scale, dir2);
}
