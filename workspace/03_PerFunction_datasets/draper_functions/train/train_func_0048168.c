ReadFromFile(char* pBuffer, int maxLen)
{


#ifndef __WXMSW__
	if (m_binary)
#endif
		return m_pFile->Read(pBuffer, maxLen);

#ifndef __WXMSW__


	const int readLen = maxLen / 2;

	char* r = pBuffer + readLen;
	int len = m_pFile->Read(r, readLen);
	if (!len || len == wxInvalidOffset)
		return len;

	const char* const end = r + len;
	char* w = pBuffer;


	while (r != end)
	{
		char c = *r++;
		if (c == '\n')
		{
			if (!m_wasCarriageReturn)
				*w++ = '\r';
			m_wasCarriageReturn = false;
		}
		else if (c == '\r')
			m_wasCarriageReturn = true;
		else
			m_wasCarriageReturn = false;

		*w++ = c;
	}

	return w - pBuffer;
#endif
}
