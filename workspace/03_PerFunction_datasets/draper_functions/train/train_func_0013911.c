pause(bool p_locked) {

	m_timer->stop();
	if (p_locked) {
		m_state = PAUSED_LOCKED;
	} else {
		m_state = PAUSED_UNLOCKED;
	}
	emit(pauseChanged(true, false));
}
