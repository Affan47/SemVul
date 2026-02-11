goto_position(const TokenizerPos& pos) {
	Tokenizer::goto_position(pos);
	int offs = 0;
	for (int idx = 0; idx < m_len; idx++) {
		char ch = m_tokens[idx];
		if (ch == '\t') {
			offs = (offs/8 + 1)*8;
		} else {
			offs++;
		}
		if (offs == pos.getColumn() - 1) {
			m_pos = idx;
			if (m_pos < m_len) {
				m_token_at_end = 0;
			}
			break;
		}
	}
}
