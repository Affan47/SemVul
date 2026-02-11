puttRelease()
{
	if (!m_useAdvancedPutting && putting && !editing)
	{
		putting = false;
		stroking = true;
	}
}
