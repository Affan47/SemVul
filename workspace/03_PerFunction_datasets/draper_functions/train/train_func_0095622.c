py_attack(int y, int x) {
	int blow_energy = 10000 / p_ptr->state.num_blows;
	int blows = 0;
	bool fear = FALSE;
	monster_type *m_ptr = cave_monster(cave, cave->m_idx[y][x]);


	disturb(p_ptr, 0,0);


	p_ptr->energy_use = 0;


	while (p_ptr->energy >= blow_energy * (blows + 1)) {
		bool stop = py_attack_real(y, x, &fear);
		p_ptr->energy_use += blow_energy;
		if (stop || p_ptr->energy_use + blow_energy > 100) break;
		blows++;
	}


	if (fear && m_ptr->ml) {
		char m_name[80];
		monster_desc(m_name, sizeof(m_name), m_ptr, 0);
		add_monster_message(m_name, cave->m_idx[y][x], MON_MSG_FLEE_IN_TERROR, TRUE);
	}
}
