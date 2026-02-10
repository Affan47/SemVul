make_ranged_throw(object_type *o_ptr, int y, int x) {
	struct attack_result result = {FALSE, 0, 0, "hit"};

	monster_type *m_ptr = cave_monster(cave, cave->m_idx[y][x]);
	monster_race *r_ptr = &r_info[m_ptr->r_idx];

	int bonus = p_ptr->state.to_h + o_ptr->to_h;
	int chance = p_ptr->state.skills[SKILL_TO_HIT_THROW] + bonus * BTH_PLUS_ADJ;
	int chance2 = chance - distance(p_ptr->py, p_ptr->px, y, x);

	int multiplier = 1;
	const struct slay *best_s_ptr = NULL;


	if (!test_hit(chance2, r_ptr->ac, m_ptr->ml)) return result;

	result.success = TRUE;

	improve_attack_modifier(o_ptr, m_ptr, &best_s_ptr, TRUE, FALSE);


	if (best_s_ptr != NULL) {
		result.hit_verb = best_s_ptr->range_verb;
		multiplier += best_s_ptr->mult;
	}


	result.dmg = damroll(o_ptr->dd, o_ptr->ds);
	result.dmg += o_ptr->to_d;
	result.dmg *= multiplier;
	result.dmg = critical_norm(o_ptr->weight, o_ptr->to_h, result.dmg, &result.msg_type);

	return result;
}
