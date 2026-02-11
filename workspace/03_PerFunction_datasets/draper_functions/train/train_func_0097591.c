mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (!m_owner->isSelected()) {
		event->ignore();
		return;
	}

	if (m_spaceBarWasPressed) {
		event->ignore();
		return;
	}


	if (m_doDrag) {
		m_owner->partLabelMoved(m_initialPosition, m_initialOffset, pos(), m_offset);
	}

	QGraphicsSvgItem::mouseReleaseEvent(event);
}
