unlockBlock(int nr) {
	if (m_current_block) {
		m_current_block = NULL;

		return TRUE;
	}

	return FALSE;
}
