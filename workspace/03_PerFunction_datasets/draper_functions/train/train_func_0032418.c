Put2(const byte *inString, size_t length, int messageEnd, bool blocking)
{
	FILTER_BEGIN;
	if (m_putMessage)
		FILTER_OUTPUT3(1, 0, inString, length, 0, m_messagePutChannel);
	m_hashModule.Update(inString, length);
	if (messageEnd)
	{
		{
			size_t size;
			m_space = HelpCreatePutSpace(*AttachedTransformation(), m_hashPutChannel, m_digestSize, m_digestSize, size = m_digestSize);
			m_hashModule.TruncatedFinal(m_space, m_digestSize);
		}
		FILTER_OUTPUT3(2, 0, m_space, m_digestSize, messageEnd, m_hashPutChannel);
	}
	FILTER_END_NO_MESSAGE_END;
}
