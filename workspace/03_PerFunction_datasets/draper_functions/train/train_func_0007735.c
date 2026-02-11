create_unit(int unitId, int townRecno, int unitHasJob)
{


   SpriteInfo* spriteInfo = sprite_res[unit_res[unitId]->sprite_id];
   int         xLoc=loc_x1, yLoc=loc_y1;

	if(!locate_space(remove_firm, xLoc, yLoc, loc_x2, loc_y2, spriteInfo->loc_width, spriteInfo->loc_height))
		return 0;


	int unitNationRecno;

	if( townRecno )
		unitNationRecno = town_array[townRecno]->nation_recno;
	else
		unitNationRecno = nation_recno;

	int unitRecno = unit_array.add_unit( unitId, unitNationRecno, RANK_SOLDIER, 0, xLoc, yLoc );


	if( townRecno )
		town_array[townRecno]->dec_pop(unit_array[unitRecno]->race_id, unitHasJob);

	return unitRecno;
}
