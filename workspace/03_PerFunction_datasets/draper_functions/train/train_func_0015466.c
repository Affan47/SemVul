wr_monsters(void)
{
	int i;
	size_t j;

	if (p_ptr->is_dead)
		return;


	wr_u16b(cave_monster_max(cave));


	for (i = 1; i < cave_monster_max(cave); i++) {
		byte unaware = 0;

		const monster_type *m_ptr = cave_monster(cave, i);

		wr_s16b(m_ptr->r_idx);
		wr_byte(m_ptr->fy);
		wr_byte(m_ptr->fx);
		wr_s16b(m_ptr->hp);
		wr_s16b(m_ptr->maxhp);
		wr_byte(m_ptr->mspeed);
		wr_byte(m_ptr->energy);
		wr_byte(MON_TMD_MAX);

		for (j = 0; j < MON_TMD_MAX; j++)
			wr_s16b(m_ptr->m_timed[j]);

		if (m_ptr->unaware) unaware |= 0x01;
		wr_byte(unaware);

		for (j = 0; j < OF_BYTES && j < OF_SIZE; j++)
			wr_byte(m_ptr->known_pflags[j]);
		if (j < OF_BYTES) pad_bytes(OF_BYTES - j);

		wr_byte(0);
	}
}
