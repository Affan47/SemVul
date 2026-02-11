equals(ParserError* err) const {
	return (m_txt == err->m_txt &&
	        m_fname == err->m_fname &&
		m_pos.equals(err->m_pos));
}
