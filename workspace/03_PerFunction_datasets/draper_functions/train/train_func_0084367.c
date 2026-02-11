max_attack_range()
{
	int maxRange=0;
	AttackInfo *attackInfo = unit_res.get_attack_info(unit_res[unit_id]->first_attack);
	int attackCount = unit_res[unit_id]->attack_count;

	for(int i=0; i<attackCount; i++, attackInfo++)
	{
		if(combat_level >= attackInfo->combat_level &&
			attackInfo->attack_range>maxRange)
			maxRange = attackInfo->attack_range;
	}

	return maxRange;
}
