updateMask()
{
	if (m_header_visible || m_footer_visible) {
		setMask(rect().adjusted(0, m_header_visible, 0, m_footer_visible));
		setAttribute(Qt::WA_TransparentForMouseEvents, true);
	} else {
		clearMask();
		setAttribute(Qt::WA_TransparentForMouseEvents, false);
		raise();

		if (m_scenes->isVisible()) {
			QApplication::processEvents();
			m_scenes->update();
			m_scenes->clearFocus();
			m_scenes->setFocus();
		}
	}
}
