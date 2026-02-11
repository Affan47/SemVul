setExpandable(bool expandable)
{
	m_always_expanded = !expandable;
	if (m_always_expanded) {
		m_text->setText(m_long_text);
		m_expander->hide();
	} else if (m_short_text != m_long_text) {
		m_expanded = true;
		expanderToggled();
	}
}
