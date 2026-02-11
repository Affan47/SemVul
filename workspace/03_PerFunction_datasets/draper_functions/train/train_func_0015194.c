simpleConnectedMoved(ConnectorItem * from, ConnectorItem * to)
{
	if (from == NULL) return;


	QPointF p1, p2;
	calcNewLine(from, to, p1, p2);


	this->setPos(p1);
	this->setLine(0,0, p2.x() - p1.x(), p2.y() - p1.y() );

	setConnector1Rect();
}
