readNextToken() {
	char ch = m_Sep;
	while (isSepChar(ch) && !m_File.eof()) {
		m_File.read(&ch, 1);
	}
	int count = 0;
	while (count < m_Max && !isSepChar(ch) && !m_File.eof()) {
		if (ch != m_Sep) m_LastToken[count++] = ch;
		m_File.read(&ch, 1);
	}
	m_LastToken[count] = 0;
	while (!isSepChar(ch) && !m_File.eof()) {
		m_File.read(&ch, 1);
	}
	if (m_File.eof()) {
		m_IsOK = 0;
	}
}
