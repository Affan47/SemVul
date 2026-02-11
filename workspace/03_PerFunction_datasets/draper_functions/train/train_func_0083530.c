getTotalMessageSize(void) const
{
	CMT_CHECKASSERT
	if (m_buffer->m_length == 255)
		return ((uint16_t) m_buffer->m_datlen.m_extended.m_length.m_high * 256 + (uint16_t) m_buffer->m_datlen.m_extended.m_length.m_low) + CMT_LEN_MSGEXTHEADERCS;
	else
		return m_buffer->m_length + CMT_LEN_MSGHEADERCS;
}
