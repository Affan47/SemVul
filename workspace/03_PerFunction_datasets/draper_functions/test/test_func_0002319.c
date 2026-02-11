Update(const UINT_8* pbData, UINT_32 uLen)
{
	UINT_32 j = ((m_count[0] >> 3) & 0x3F);

	if((m_count[0] += (uLen << 3)) < (uLen << 3))
		++m_count[1];

	m_count[1] += (uLen >> 29);

	UINT_32 i;
	if((j + uLen) > 63)
	{
		i = 64 - j;
		memcpy(&m_buffer[j], pbData, i);
		Transform(m_state, m_buffer);

		for( ; (i + 63) < uLen; i += 64)
			Transform(m_state, &pbData[i]);

		j = 0;
	}
	else i = 0;

	if((uLen - i) != 0)
		memcpy(&m_buffer[j], &pbData[i], uLen - i);
}
