drawRotator(QPainter *p, QPointF origin, int corner, double half_size, QPen pen)
{


	p->setPen(pen);
	p->save();
	p->translate(origin);


	if (corner == GLEDrawingArea::TopLeft)
		p->rotate(-90.0);
	else if (corner == GLEDrawingArea::BottomLeft)
		p->rotate(180.0);
	else if (corner == GLEDrawingArea::BottomRight)
		p->rotate(90.0);


	p->drawEllipse(QRectF(-half_size, -half_size, 2*half_size, 2*half_size));

	p->restore();
}
