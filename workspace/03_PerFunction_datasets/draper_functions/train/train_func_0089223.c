setControlPoints(const QPolygon& pa)
{
	_points = pa;

	QPainterPath path;
	path.moveTo(pa[0]);
	for (int i = 1; i < pa.size(); i += 3)
		path.cubicTo(pa[i], pa[(i + 1) % pa.size()], pa[(i + 2) % pa.size()]);

	setPath(path);
}
