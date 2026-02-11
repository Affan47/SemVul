operator== (TextTag const& tag) const
{
	if (tag.GetTag () != GetTag ())
		return false;
	return static_cast <PositionTextTag const&> (tag).m_Position == m_Position;
}
