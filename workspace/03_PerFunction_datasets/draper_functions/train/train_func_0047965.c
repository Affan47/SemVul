independent_unit_join_nation(int raceId, int toNationRecno)
{


	int unitRecno = mobilize_town_people(raceId, 1, 0);

	if( !unitRecno )
		return 0;

	Unit* unitPtr = unit_array[unitRecno];


	int skillId, skillLevel, combatLevel;

	switch( misc.random(3) )
	{
		case 0:
			skillId = SKILL_LEADING;

			if( misc.random(3)==0 )
				skillLevel = misc.random(100);
			else
				skillLevel = misc.random(50);

			combatLevel = skillLevel + misc.random(40) - 20;
         combatLevel = MIN(combatLevel, 100);
			combatLevel = MAX(combatLevel, 10);
			break;

		case 1:
			skillId = 0;
			skillLevel = 0;
			combatLevel = 10 + misc.random(10);
			break;

		case 2:
			skillId = misc.random(MAX_TRAINABLE_SKILL)+1;
			{
				int loopCount=0;

				while( skillId==SKILL_SPYING )
				{
					if( ++skillId > MAX_TRAINABLE_SKILL )
						skillId = 1;

					err_when( ++loopCount > 100 );
				}
			}
			skillLevel = 10+misc.random(80);
			combatLevel = 10+misc.random(30);
			break;
	}


	unitPtr->skill.skill_id = skillId;
	unitPtr->skill.skill_level = skillLevel;
	unitPtr->set_combat_level( combatLevel );


	if( !unitPtr->betray(toNationRecno) )
		return 0;


	unitPtr->ai_move_to_nearby_town();


	nation_array[toNationRecno]->last_independent_unit_join_date = info.game_date;

	return 1;
}
