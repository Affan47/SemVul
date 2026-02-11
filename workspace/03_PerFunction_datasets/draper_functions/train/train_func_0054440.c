toBinary(struct uuid &u) const
{
	memset(&u, 0, sizeof(u));
	if(m_bIsValid)
	    memcpy(&u, &m_uuid, sizeof(u));

	return m_bIsValid;
}
