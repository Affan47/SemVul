setTitle(const QString &title) {
	if(m_title != title) {
		m_title = title;
		if (m_binLabel) m_binLabel->setText(title);
	}
}
