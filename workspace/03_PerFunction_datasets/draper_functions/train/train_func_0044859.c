GetDisplayString() const
{
	return CFormat(wxGetTranslation(m_label)) %
		CastSecondsToHM(m_value ? GetTimerSeconds() : 0);
}
