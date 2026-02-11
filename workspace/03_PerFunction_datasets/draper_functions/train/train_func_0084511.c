status_check_no_magic_damage(struct block_list *bl)
{
	nullpo_retr(0, bl);

	if(bl->type == BL_PC)
	{
		if(((struct map_session_data*)bl)->special_state.no_magic_damage)
			return 1;
	}
	return 0;
}
