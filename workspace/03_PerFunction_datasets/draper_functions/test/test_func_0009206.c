playerName(Chess::Side side) const
{
	if (side == Chess::Side::White)
		return m_tags.value("White");
	else if (side == Chess::Side::Black)
		return m_tags.value("Black");

	return QString();
}
