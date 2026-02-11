Close()
{
	bool state = m_autoClosed ? true : m_file.Close();
	m_autoClosed = false;
	return state;
}
