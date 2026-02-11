addMarkerNothing(const int boxPosition)
{
	if (!m_pause && m_inputAccepted && (!m_markersNothing->containsVisible(boxPosition))) {
		m_markersNothing->insert(new KBBGraphicsItemOnBox(markerNothing, this, m_themeManager, boxPosition, m_columns, m_rows));
		m_balls->remove(boxPosition);
		m_ballsUnsure->remove(boxPosition);
		m_boardBallsPlaced->remove(boxPosition);
	}
}
