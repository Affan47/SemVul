getAp(double t, double pm1, double pm2, GLEPoint& p) {
	GLEPoint T, Tp, N, Np, c;
	m_Curve->getC(t, c);
	m_Curve->getCp(t, T);
	m_Curve->getCpp(t, Tp);

	N.setXY(T.getY(), -T.getX());
	N.normalize();

	double norm_sq = T.normSq();
	double norm = sqrt(norm_sq);
	double dnorm = (T.getX()*Tp.getX() + T.getY()*Tp.getY())/norm;
	Np.setX((Tp.getY()*norm - T.getY()*dnorm)/norm_sq);
	Np.setY((T.getX()*dnorm - Tp.getX()*norm)/norm_sq);

	double h = m_Curve->getDist(m_T0, t) * tan(m_ArrAlpha);
	double hp = m_Curve->getDistp(t) * tan(m_ArrAlpha);
	N.dotScalar(hp);
	Np.dotScalar(h);
	N.add(Np);
	N.dotScalar(pm1);

	p.set(T);
	p.add(N);
	p.normalize();
	p.dotScalar(pm2);
}
