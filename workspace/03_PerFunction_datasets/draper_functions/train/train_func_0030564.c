shape() const
{
	QRectF t = boundingRect();
	QPainterPath path;
	path.addRect(t);
    return path;
}
