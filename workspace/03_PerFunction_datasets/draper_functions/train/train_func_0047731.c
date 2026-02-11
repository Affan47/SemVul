assign_to_firm()
{
	int 	i, firmCount=firm_array.size();
	Firm* firmPtr;
	int	curXLoc = next_x_loc(), curYLoc = next_y_loc();
	BYTE	regionId = world.get_region_id(curXLoc, curYLoc);

	int firmRecno = misc.random(firm_array.size())+1;

	for( i=0 ; i<firmCount ; i++ )
	{
		if( ++firmRecno > firmCount )
			firmRecno = 1;

		if( firm_array.is_deleted(firmRecno) )
			continue;

		firmPtr = firm_array[firmRecno];

		if( firmPtr->region_id != regionId )
			continue;

		if( firmPtr->firm_id == FIRM_MONSTER )
		{
			if( ((FirmMonster*)firmPtr)->can_assign_monster(sprite_recno) )
			{
				group_order_monster(firmPtr->loc_x1, firmPtr->loc_y1, 2);
				return 1;
			}
		}
	}

	return 0;
}
