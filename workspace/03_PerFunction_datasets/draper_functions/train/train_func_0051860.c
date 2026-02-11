target_okay(void)
{

	if (!target_set) return (FALSE);


	if (target_who == 0) return (TRUE);


	if (target_who > 0)
	{
		int m_idx = target_who;


		if (target_able(m_idx))
		{
			monster_type *m_ptr = &mon_list[m_idx];


			target_y = m_ptr->fy;
			target_x = m_ptr->fx;


			return (TRUE);
		}
	}


	return (FALSE);
}
