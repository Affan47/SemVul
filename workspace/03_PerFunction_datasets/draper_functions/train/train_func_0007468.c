popState()
{
	if (m_states.isEmpty()) {
		return;
	}
	m_state = m_states.pop();
	m_cursor.setCharFormat(m_state.char_format);
	setFont(m_state.active_codepage);
}
