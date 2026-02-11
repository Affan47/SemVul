OnBnClickedPrevFile(wxCommandEvent&)
{
	if (--m_index < 0) {
		m_index = m_files.size() - 1;
	}
	m_file = m_files[m_index];
	UpdateData(true);
}
