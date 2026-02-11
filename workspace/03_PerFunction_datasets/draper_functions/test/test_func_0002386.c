mousePressEvent(QGraphicsSceneMouseEvent *event)
{


	QList<QGraphicsItem *> items = scene()->items(event->scenePos());
	if (items.contains(m_connector0) || items.contains(m_connector1)) {
		event->ignore();
		return;
	}


	setFlag(QGraphicsItem::ItemIsSelectable, true);
	ClipableWire::mousePressEvent(event);
	setFlag(QGraphicsItem::ItemIsSelectable, false);
}
