intersections(QPointF qtp1, QPointF qtp2)
{
	double m, c;
	if (qtp2.x() == qtp1.x())
		return(intersections(qtp2.x(), 0, true));

	m = (qtp2.y() - qtp1.y())/(qtp2.x()-qtp1.x());
	c = qtp2.y() - m*qtp2.x();

	return(intersections(m,c,false));
}
