drawPolygon(const QPointF* points, int pointCount, QPaintEngine::PolygonDrawMode mode)
{
	if (m_proxy)
	{
		m_painter->drawPolygon(points, pointCount, mode == WindingMode ? Qt::WindingFill : Qt::OddEvenFill);
	}
}
