getA(double t, double pm, GLEPoint& p) {
	GLEPoint N, T;

	m_Curve->getCp(t, T);
	T.normalize();

	N.setXY(T.getY(), -T.getX());

	double h = pm * m_Curve->getDist(m_T0, t) * tan(m_ArrAlpha);
	N.dotScalar(h);

	m_Curve->getC(t, p);
	p.add(N);
}
