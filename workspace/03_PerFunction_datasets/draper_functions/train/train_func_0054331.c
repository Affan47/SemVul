monster_health_attr(void)
{
	byte attr = TERM_WHITE;


	if (!p_ptr->health_who)
		attr = TERM_DARK;


	else if ((!mon_list[p_ptr->health_who].ml) ||
			(p_ptr->timed[TMD_IMAGE]) ||
			(mon_list[p_ptr->health_who].hp < 0))
	{

		attr = TERM_WHITE;
	}

	else
	{
		int pct;

		monster_type *m_ptr = &mon_list[p_ptr->health_who];


		attr = TERM_RED;


		pct = 100L * m_ptr->hp / m_ptr->maxhp;


		if (pct >= 10) attr = TERM_L_RED;


		if (pct >= 25) attr = TERM_ORANGE;


		if (pct >= 60) attr = TERM_YELLOW;


		if (pct >= 100) attr = TERM_L_GREEN;


		if (m_ptr->monfear) attr = TERM_VIOLET;


		if (m_ptr->confused) attr = TERM_UMBER;


		if (m_ptr->stunned) attr = TERM_L_BLUE;


		if (m_ptr->csleep) attr = TERM_BLUE;
	}

	return attr;
}
