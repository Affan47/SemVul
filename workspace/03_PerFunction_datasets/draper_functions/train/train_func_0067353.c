close_tokens() {
	if (m_fb != NULL) {
		m_fb->close();
		delete m_fb;
		m_fb = NULL;
		delete m_is;
		m_is = NULL;
	}
}
