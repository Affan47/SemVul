draw(QPainter *p)
{
	if (!isActive())
		return;
	p->setPen(QGLE::osnapLinePen());
	p->drawLine(getQtPoint(StartPoint), getQtPoint(EndPoint));
}
