Create(wxFile* pFile, bool read, bool binary)
{
	wxASSERT(pFile);
	delete m_pFile;
	m_pFile = pFile;
	m_read = read;
	m_binary = binary;

	if (read)
	{
		m_curAppBuf = BUFFERCOUNT - 1;
		m_curThreadBuf = 0;
	}
	else
	{
		m_curAppBuf = -1;
		m_curThreadBuf = 0;
	}

	m_running = true;
	wxThreadEx::Create();
	wxThreadEx::Run();

	return true;
}
