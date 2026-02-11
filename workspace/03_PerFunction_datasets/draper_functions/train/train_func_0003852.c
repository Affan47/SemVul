SetEditing (bool editing)
{
	if (editing) {
		if (m_BlinkSignal != 0)
			return;
		m_BlinkSignal = g_timeout_add (CURSOR_ON_TIME, on_blink, this);
		m_CursorVisible = true;
	} else {
		if (m_BlinkSignal == 0)
			return;
		g_source_remove (m_BlinkSignal);
		m_BlinkSignal = 0;
		m_CursorVisible = false;
	}
	SetPosition (m_x, m_y);
}
