itemChange(GraphicsItemChange change, const QVariant &value)
{
	switch (change) {
		case QGraphicsItem::ItemSceneHasChanged:
			if (scaling()) {
				ZoomableGraphicsView *sw = dynamic_cast<ZoomableGraphicsView*>(scene()->parent());
				if (sw) {
					connect(sw, SIGNAL(zoomChanged(double)), this, SLOT(zoomChangedSlot(double)));
				}

			}
			break;
		default:
			break;
   	}

    return QGraphicsPixmapItem::itemChange(change, value);
}
