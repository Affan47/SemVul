distanceToPoint(const QPointF& p, QPointF *nearestPoint)
{
	QPointF amovePoint = getQtPoint(CentrePoint);
	if (nearestPoint)
		*nearestPoint = amovePoint;
	return(QGLE::distance(amovePoint, p));
}
