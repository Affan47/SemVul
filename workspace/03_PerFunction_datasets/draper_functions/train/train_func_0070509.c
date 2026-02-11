think_attack_neighbor()
{


	if( patrol_unit_count > 0 )
		return 0;


	int generalCount=0;

	MonsterInFirm* monsterInFirm = monster_general_array;
	int				totalCombatLevel=0;


	int i;
	for( i=0 ; i<monster_general_count ; i++, monsterInFirm++ )
	{
		if( monsterInFirm->soldier_count >= 5 )
			generalCount++;
	}

	if( generalCount<=1 )
		return 0;


	int		 xOffset, yOffset;
	int		 xLoc, yLoc;
	int		 attackFlag=0;
	FirmInfo* firmInfo = firm_res[firm_id];
	Location* locPtr;

	int scanLocWidth  = MONSTER_ATTACK_NEIGHBOR_RANGE*2;
	int scanLocHeight = MONSTER_ATTACK_NEIGHBOR_RANGE*2;
	int scanLimit = scanLocWidth * scanLocHeight;
	short targetNation;

	for(i=firmInfo->loc_width*firmInfo->loc_height+1; i<=scanLimit; i++)
	{
		misc.cal_move_around_a_point(i, scanLocWidth, scanLocHeight, xOffset, yOffset);

		xLoc = center_x + xOffset;
		yLoc = center_y + yOffset;

		xLoc = MAX(0, xLoc);
		xLoc = MIN(MAX_WORLD_X_LOC-1, xLoc);

		yLoc = MAX(0, yLoc);
		yLoc = MIN(MAX_WORLD_Y_LOC-1, yLoc);

		locPtr = world.get_loc(xLoc, yLoc);

		if(locPtr->is_firm())
		{
			Firm *firmPtr = firm_array[locPtr->firm_recno()];
			if(firmPtr->nation_recno)
			{
				targetNation = firmPtr->nation_recno;
				attackFlag = 1;
				xLoc = firmPtr->loc_x1;
				yLoc = firmPtr->loc_y1;
				break;
			}
		}
		else if(locPtr->is_town())
		{
			Town *townPtr = town_array[locPtr->town_recno()];
			if(townPtr->nation_recno)
			{
				targetNation = townPtr->nation_recno;
				attackFlag = 1;
				xLoc = townPtr->loc_x1;
				yLoc = townPtr->loc_y1;
				break;
			}
		}
	}

	if( !attackFlag )
		return 0;


	current_monster_action_mode = MONSTER_ACTION_ATTACK;

	mobilize_general( misc.random(monster_general_count)+1 );

	if( patrol_unit_count > 0 )
	{

		set_hostile_nation(targetNation);


		unit_array.attack(xLoc, yLoc, 0, patrol_unit_array, patrol_unit_count, COMMAND_AI, 0);

		return 1;
	}
	else
		return 0;
}
