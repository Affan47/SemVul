ignoreAt(int x, int y, bool force)
{
	if (force || this->focusModel() == MOUSEFOCUS) {
		m_ignore_mouse_x = x; m_ignore_mouse_y = y;
	}
}
