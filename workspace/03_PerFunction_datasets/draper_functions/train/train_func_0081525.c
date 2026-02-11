stretchBy(QPointF howMuch) {
	if (!m_rubberBandLeg) return;

	Q_UNUSED(howMuch);

	resetLeg(m_oldPolygon, false, m_activeStretch, "move");


	m_attachedTo->update();
}
