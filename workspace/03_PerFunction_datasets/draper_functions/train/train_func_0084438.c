registered ()
{
	if (!m_bLoaded) return false;

	if (!m_bRegistered) return false;
	return (m_iStatus ? true : false);
}
