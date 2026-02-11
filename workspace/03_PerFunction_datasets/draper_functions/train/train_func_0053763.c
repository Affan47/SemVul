is_next_token(const char* token) throw(ParserError) {
	get_token();
	if (m_token.length() == 0) {
		return m_token == token;
	} else {
		if (m_token == token) {
			return 1;
		}
		pushback_token();
		return 0;
	}
}
