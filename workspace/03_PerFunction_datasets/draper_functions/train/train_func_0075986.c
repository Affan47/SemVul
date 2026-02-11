mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	if (m_features & Draggable)
		emit dragged(event->scenePos() - event->lastScenePos());
	else
		QGraphicsItem::mouseMoveEvent(event);
}
