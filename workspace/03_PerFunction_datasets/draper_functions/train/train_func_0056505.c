OnBnClickedNextFile(wxCommandEvent&)
{
	if (++m_index == (int) m_files.size()) {
		m_index = 0;
	}
	m_file = m_files[m_index];
	UpdateData(true);
}
