calculate_program_heat_cost(int program_id)
{

	float cost_ratio[NUMBER_OF_SKILL_LEVELS] = { 1.0, 0.9, 0.81, 0.73, 0.66, 0.59, 0.53, 0.48, 0.43, 0.39 };

	if (program_id == get_program_index_with_name("Emergency shutdown") ) {
		return (1/cost_ratio[Me.spellcasting_skill]) * (SpellSkillMap[program_id].heat_cost +
							    	SpellSkillMap[program_id].heat_cost_per_level * (Me.skill_level[program_id] - 1));
	} else {
		return cost_ratio[Me.spellcasting_skill] * (SpellSkillMap[program_id].heat_cost +
							    SpellSkillMap[program_id].heat_cost_per_level * (Me.skill_level[program_id] - 1));
	}
}
