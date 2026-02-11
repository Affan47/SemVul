renderHints() const
{
	QPainter::RenderHints hint = QPainter::TextAntialiasing;
	if (m_antialias)
		hint |= QPainter::Antialiasing;

	return hint;
}
