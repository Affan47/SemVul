itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant & value)
{
	switch (change) {
		case QGraphicsItem::ItemSelectedChange:
			if (m_partLabel) {
				m_partLabel->ownerSelected(value.toBool());
			}

			break;
		default:
			break;
	}

	return QGraphicsSvgItem::itemChange(change, value);
}
