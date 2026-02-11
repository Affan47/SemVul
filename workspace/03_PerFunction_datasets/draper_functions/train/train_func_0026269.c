insideInnerCircle(ConnectorItem * connectorItem, QPointF scenePos)
{
	QPointF localPos = connectorItem->mapFromScene(scenePos);
	double rad = connectorItem->radius();
	if (rad <= 0) return false;

	rad -= ((connectorItem->strokeWidth() / 2.0));

	QRectF r = connectorItem->rect();
	QPointF c = r.center();
	if ( (localPos.x() - c.x()) * (localPos.x() - c.x()) + (localPos.y() - c.y()) * (localPos.y() - c.y())  < rad * rad ) {

		return true;
	}

	return false;
}
