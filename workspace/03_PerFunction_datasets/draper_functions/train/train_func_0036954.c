DoWrite(const char* pBuffer, int len)
{
	int fd = m_pFile->fd();
	if (wxWrite(fd, pBuffer, len) == len)
		return true;

	int code = wxSysErrorCode();

	const wxString error = wxSysErrorMsg(code);

	wxMutexLocker locker(m_mutex);
	delete [] m_error_description;
	m_error_description = new wxChar[error.Len() + 1];
	wxStrcpy(m_error_description, error);

	return false;
}
