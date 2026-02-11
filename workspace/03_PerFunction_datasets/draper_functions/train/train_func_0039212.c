hit_building()
{
	short damageXLoc = damage_x_loc();
	short damageYLoc = damage_y_loc();
	if( damageXLoc < 0 || damageXLoc >= world.max_x_loc ||
		damageYLoc < 0 || damageYLoc >= world.max_y_loc)
		return;

	Location* locPtr = world.get_loc(damageXLoc, damageYLoc);


	if(locPtr->is_firm() )

	{
		Firm *firmPtr = firm_array[locPtr->firm_recno()];
		firmPtr->hit_points -= attack_damage*2;
		if( firmPtr->hit_points <= 0)
		{
			firmPtr->hit_points = (float) 0;

			se_res.sound(firmPtr->center_x, firmPtr->center_y, 1,
				'F', firmPtr->firm_id, "DIE" );

			firm_array.del_firm(locPtr->firm_recno());
		}
	}

	if( locPtr->is_town() )
	{
		Town *townPtr = town_array[locPtr->town_recno()];
		if( (life_time % 30) == 0 )
			townPtr->kill_town_people(0);
	}

}
