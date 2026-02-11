monster_swap(int y1, int x1, int y2, int x2)
{
	int m1, m2;

	monster_type *m_ptr;

	monster_race *r_ptr;


	m1 = cave_m_idx[y1][x1];
	m2 = cave_m_idx[y2][x2];


	cave_m_idx[y1][x1] = m2;
	cave_m_idx[y2][x2] = m1;


	if (m1 > 0)
	{
		m_ptr = &mon_list[m1];


		m_ptr->fy = y2;
		m_ptr->fx = x2;


		update_mon(m1, TRUE);


		r_ptr = &r_info[m_ptr->r_idx];
		if (rf_has(r_ptr->flags, RF_HAS_LITE)) p_ptr->redraw |= PU_UPDATE_VIEW;


		p_ptr->redraw |= (PR_MONLIST);
	}


	else if (m1 < 0)
	{

		p_ptr->py = y2;
		p_ptr->px = x2;


		p_ptr->redraw |= (PR_DTRAP);


		p_ptr->update |= (PU_PANEL);


		p_ptr->update |= (PU_UPDATE_VIEW | PU_DISTANCE);


		p_ptr->update |= (PU_UPDATE_FLOW);


		p_ptr->redraw |= (PR_MONLIST);
	}


	if (m2 > 0)
	{
		m_ptr = &mon_list[m2];


		m_ptr->fy = y1;
		m_ptr->fx = x1;


		update_mon(m2, TRUE);


		r_ptr = &r_info[m_ptr->r_idx];
		if (rf_has(r_ptr->flags, RF_HAS_LITE)) p_ptr->update |= PU_UPDATE_VIEW;


		p_ptr->redraw |= (PR_MONLIST);
	}


	else if (m2 < 0)
	{

		p_ptr->py = y1;
		p_ptr->px = x1;


		p_ptr->redraw |= (PR_DTRAP);


		p_ptr->update |= (PU_PANEL);


		p_ptr->update |= (PU_UPDATE_VIEW | PU_DISTANCE);


		p_ptr->update |= (PU_UPDATE_FLOW);


		p_ptr->redraw |= (PR_MONLIST);
	}


	light_spot(y1, x1);
	light_spot(y2, x2);
}
