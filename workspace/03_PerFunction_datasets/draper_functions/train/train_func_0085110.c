hit_target()
{


	short damageXLoc = damage_x_loc();
	short damageYLoc = damage_y_loc();
	if( damageXLoc < 0 || damageXLoc >= world.max_x_loc ||
		damageYLoc < 0 || damageYLoc >= world.max_y_loc)
		return;

	Location *locPtr = world.get_loc(damageXLoc, damageYLoc);

	Unit *targetUnit;
	if( locPtr->has_unit(UNIT_AIR))
	{
		targetUnit = unit_array[locPtr->unit_recno(UNIT_AIR)];
		targetUnit->hit_points -= 2*attack_damage;
		if( targetUnit->hit_points <= 0)
			targetUnit->hit_points = (float) 0;
	}

	if( locPtr->has_unit(UNIT_LAND))
	{
		targetUnit = unit_array[locPtr->unit_recno(UNIT_LAND)];
		targetUnit->hit_points -= attack_damage;
		if( targetUnit->hit_points <= 0)
			targetUnit->hit_points = (float) 0;
	}
	else if( locPtr->has_unit(UNIT_SEA))
	{
		targetUnit = unit_array[locPtr->unit_recno(UNIT_SEA)];
		targetUnit->hit_points -= attack_damage;
		if( targetUnit->hit_points <= 0)
			targetUnit->hit_points = (float) 0;
	}
	else
	{
		hit_building();
	}

	hit_plant();
	hit_fire();
}
