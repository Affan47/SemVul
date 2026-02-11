closeDevice()
{
	delete m_sigMapper;
	m_sigMapper = NULL;
	m_capStartAct->setEnabled(false);
	m_capStartAct->setChecked(false);
	if (fd() >= 0) {
		if (m_capNotifier) {
			delete m_capNotifier;
			delete m_capImage;
			m_capNotifier = NULL;
			m_capImage = NULL;
		}
		if (m_ctrlNotifier) {
			delete m_ctrlNotifier;
			m_ctrlNotifier = NULL;
		}
		delete m_frameData;
		m_frameData = NULL;
		v4lconvert_destroy(m_convertData);
		v4l2::close();
		delete m_capture;
		m_capture = NULL;
	}
	while (QWidget *page = m_tabs->widget(0)) {
		m_tabs->removeTab(0);
		delete page;
	}
	m_ctrlMap.clear();
	m_widgetMap.clear();
	m_classMap.clear();
}
