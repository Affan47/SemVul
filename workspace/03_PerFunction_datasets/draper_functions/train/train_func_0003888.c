_k_update()
{

	if (m_alignment)
	{

		QRectF baseRect;
		QGraphicsItem* parentItem = m_board->parentItem();
		if (parentItem)
		{
			baseRect = parentItem->boundingRect();
		}
		else
		{
			QGraphicsScene* scene = m_board->scene();
			baseRect = scene ? scene->sceneRect() : QRectF(QPointF(), m_size);
		}

		const qreal scaleX = baseRect.width() / m_logicalSize.width();
		const qreal scaleY = baseRect.height() / m_logicalSize.height();
		m_size = qMin(scaleX, scaleY) * m_logicalSize;
		QRectF physicalRect(baseRect.topLeft(), m_size);

		const bool hReverse = !(m_alignment & Qt::AlignAbsolute) && QApplication::isRightToLeft();
		if (m_alignment & Qt::AlignHCenter)
		{
			const qreal dx = (baseRect.width() - m_size.width()) / 2;
			physicalRect.translate(dx, 0);
		}
		else if (m_alignment & Qt::AlignRight || ((m_alignment & Qt::AlignLeft) && hReverse))
		{
			physicalRect.moveRight(baseRect.right());
		}

		if (m_alignment & Qt::AlignVCenter)
		{
			const qreal dy = (baseRect.height() - m_size.height()) / 2;
			physicalRect.translate(0, dy);
		}
		else if (m_alignment & Qt::AlignBottom)
		{
			physicalRect.moveBottom(baseRect.bottom());
		}
		m_board->setPos(physicalRect.topLeft());
	}

	m_renderSizeFactor.setX(m_size.width() / m_logicalSize.width());
	m_renderSizeFactor.setY(m_size.height() / m_logicalSize.height());
	m_board->setTransform(QTransform::fromScale(m_renderSizeFactor.x(), m_renderSizeFactor.y()));
	m_renderSizeFactor *= m_physicalSizeFactor;

	QList<Tagaro::SpriteObjectItem*>::const_iterator it1 = m_items.constBegin(), it2 = m_items.constEnd();
	for (; it1 != it2; ++it1)
		update(*it1);
}
