setShortcut(const QKeySequence& shortcut)
{
	setShortcut(shortcut, QKeySequence());
	m_reset_button->setHidden(true);
}
