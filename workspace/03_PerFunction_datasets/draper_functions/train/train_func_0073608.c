hoverShape() const
{

    QPainterPath path;
    path.addRect(0, 0, m_size.width(), m_size.height());

	if (!hasRubberBandLeg()) return path;

	foreach (ConnectorItem * connectorItem, cachedConnectorItemsConst()) {
		if (connectorItem->hasRubberBandLeg()) {
			path.addPath(connectorItem->mapToParent(connectorItem->hoverShape()));
		}
	}

	path.setFillRule(Qt::WindingFill);
	return path;
}
