computeMaxCountBeforeColliding() {
	m_maxCountBeforeColliding = 1;

	if (m_right){
		int rightCount = m_right->computeMaxCountBeforeColliding();
		if (m_right->m_colliding == m_colliding)
			m_maxCountBeforeColliding += rightCount;
	}

	if (m_next) {
		int nextMaxCountBeforeColliding = m_next->computeMaxCountBeforeColliding();
		if (m_next->m_colliding == m_colliding)
			return qMax(m_maxCountBeforeColliding, nextMaxCountBeforeColliding);
	}
	return m_maxCountBeforeColliding;
}
