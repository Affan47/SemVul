mouseReleaseEvent (QGraphicsSceneMouseEvent* event)
{

	QGraphicsItem::mouseReleaseEvent(event);

	qreal dropX = event->scenePos().x();
	qreal dropY = event->scenePos().y();

	if ((dropX==m_dragX) && (dropY==m_dragY)) {
		setCursor(Qt::ArrowCursor);
		if ((position()!=NO_POSITION) && (position()<(m_columns*m_rows)))
			m_widget->mouseBoxClick(event->button(), position());
	} else if (isMovable()) {
		setCursor(Qt::ArrowCursor);

		if ((boxPosition(dropX, dropY)==NO_POSITION) || (boxPosition(dropX, dropY)==boxPosition(m_dragX, m_dragY)) || (boxPosition(dropX, dropY)>=m_columns*m_rows))

			setPos(m_dragXPos, m_dragYPos);
		else {
			if (m_itemType==KBBScalableGraphicWidget::markerNothing)
				setBoxPosition(m_widget->moveMarkerNothing(boxPosition(m_dragX, m_dragY), boxPosition(dropX, dropY)));
			else {
				int newPos = m_widget->positionAfterMovingBall(boxPosition(m_dragX, m_dragY), boxPosition(dropX, dropY));


				if ((m_boxPosition==NO_POSITION) || (m_boxPosition>=(m_columns*m_rows))) {
					if (newPos==m_boxPosition)
						setPos(m_dragXPos, m_dragYPos);
					else
						m_widget->moveBall(boxPosition(m_dragX, m_dragY), boxPosition(dropX, dropY));
				} else
					setBoxPosition(m_widget->moveBall(boxPosition(m_dragX, m_dragY), boxPosition(dropX, dropY)));
			}
		}
	}
}
