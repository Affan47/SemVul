rd_player_hp(u32b version)
{
	int i;
	u16b tmp16u;


	rd_u16b(&tmp16u);


	if (tmp16u > PY_MAX_LEVEL)
	{
		note(format("Too many (%u) hitpoint entries!", tmp16u));
		return (-1);
	}


	for (i = 0; i < tmp16u; i++)
		rd_s16b(&p_ptr->player_hp[i]);

	return 0;
}
