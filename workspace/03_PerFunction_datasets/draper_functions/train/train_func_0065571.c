ClearDecompressorTable(void)
{
	for( int i = 0; i < m_clearCode; i++ ) {
		m_strings[i].resize(1);
		m_strings[i][0] = (char)i;
	}
	m_nextCode = m_endCode + 1;

	m_codeSize = m_minCodeSize + 1;
	m_codeMask = (1 << m_codeSize) - 1;
	m_oldCode = MAX_LZW_CODE;
}
