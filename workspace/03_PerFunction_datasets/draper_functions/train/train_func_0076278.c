GetLastSegment() const
{
	if (!HasParent())
		return _T("");

	if (!m_data->m_segments.empty())
		return m_data->m_segments.back();
	else
		return _T("");
}
