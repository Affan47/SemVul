colpm(struct message *m, int cl, int *cc, int *uc)
{
	if (cl) {
		if (m->m_collapsed > 0)
			(*uc)++;
		if ((m->m_flag & (MNEW|MREAD)) != MNEW || m->m_collapsed < 0)
			m->m_collapsed = 1;
		if (m->m_collapsed > 0)
			(*cc)++;
	} else {
		if (m->m_collapsed > 0) {
			m->m_collapsed = 0;
			(*uc)++;
		}
	}
	if (m->m_child) {
		m = m->m_child;
		colpm(m, cl, cc, uc);
		for (m = m->m_younger; m; m = m->m_younger)
			colpm(m, cl, cc, uc);
	}
}
