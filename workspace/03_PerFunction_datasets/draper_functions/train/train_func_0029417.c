setPause(bool state)
{
	m_pause = state;
	for (int i=0;i<2*(m_rows+m_columns);i++) {
		if (m_rayResults->containsVisible(i))
			m_rayResults->item(i)->setPause(state);
	}

	updateDoneButton();
}
