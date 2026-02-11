enable_should_attack_on_target(int targetXLoc, int targetYLoc)
{


	int targetNationRecno = 0;

	Location* locPtr = world.get_loc(targetXLoc, targetYLoc);

	if( locPtr->has_unit(UNIT_LAND) )
		targetNationRecno = unit_array[ locPtr->unit_recno(UNIT_LAND) ]->nation_recno;

	else if( locPtr->is_firm() )
		targetNationRecno = firm_array[locPtr->firm_recno()]->nation_recno;

	else if( locPtr->is_town() )
		targetNationRecno = town_array[locPtr->town_recno()]->nation_recno;

	if( targetNationRecno )
	{
		set_relation_should_attack(targetNationRecno, 1, COMMAND_AI);
	}
}
