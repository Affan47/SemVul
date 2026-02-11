mousePressEvent (QGraphicsSceneMouseEvent* event)
{
	m_dragXPos = x();
	m_dragYPos = y();
	m_dragX = event->scenePos().x();
	m_dragY = event->scenePos().y();

	if (isMovable()) {
		setCursor(Qt::ClosedHandCursor);
		removeInteractionInfos();
	}
}
