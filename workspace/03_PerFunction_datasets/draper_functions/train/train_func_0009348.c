remove_contradictory(artifact_type *a_ptr)
{
	if (of_has(a_ptr->flags, OF_AGGRAVATE)) of_off(a_ptr->flags, OF_STEALTH);
	if (of_has(a_ptr->flags, OF_IM_ACID)) of_off(a_ptr->flags, OF_RES_ACID);
	if (of_has(a_ptr->flags, OF_IM_ELEC)) of_off(a_ptr->flags, OF_RES_ELEC);
	if (of_has(a_ptr->flags, OF_IM_FIRE)) of_off(a_ptr->flags, OF_RES_FIRE);
	if (of_has(a_ptr->flags, OF_IM_COLD)) of_off(a_ptr->flags, OF_RES_COLD);

	if (a_ptr->pval < 0)
	{
		if (of_has(a_ptr->flags, OF_STR)) of_off(a_ptr->flags, OF_SUST_STR);
		if (of_has(a_ptr->flags, OF_INT)) of_off(a_ptr->flags, OF_SUST_INT);
		if (of_has(a_ptr->flags, OF_WIS)) of_off(a_ptr->flags, OF_SUST_WIS);
		if (of_has(a_ptr->flags, OF_DEX)) of_off(a_ptr->flags, OF_SUST_DEX);
		if (of_has(a_ptr->flags, OF_CON)) of_off(a_ptr->flags, OF_SUST_CON);
		if (of_has(a_ptr->flags, OF_CHR)) of_off(a_ptr->flags, OF_SUST_CHR);
		of_off(a_ptr->flags, OF_BLOWS);
	}

	if (of_has(a_ptr->flags, OF_LIGHT_CURSE)) of_off(a_ptr->flags, OF_BLESSED);
	if (of_has(a_ptr->flags, OF_KILL_DRAGON)) of_off(a_ptr->flags, OF_SLAY_DRAGON);
	if (of_has(a_ptr->flags, OF_KILL_DEMON)) of_off(a_ptr->flags, OF_SLAY_DEMON);
	if (of_has(a_ptr->flags, OF_KILL_UNDEAD)) of_off(a_ptr->flags, OF_SLAY_UNDEAD);
	if (of_has(a_ptr->flags, OF_DRAIN_EXP)) of_off(a_ptr->flags, OF_HOLD_LIFE);
}
