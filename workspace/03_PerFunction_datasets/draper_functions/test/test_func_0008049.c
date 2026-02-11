idle_detect_town_checking(short targetRecno)
{
   Town     *townPtr = town_array[targetRecno];
   Nation   *nationPtr = nation_recno ? nation_array[nation_recno] : NULL;
   short    targetNationRecno = townPtr->nation_recno;


   if(nation_recno)
   {
      if(targetNationRecno)
      {


			if( targetNationRecno==nation_recno )
				return 0;


			NationRelation* nationRelation = nationPtr->get_relation(targetNationRecno);

			if( nationRelation->status != NATION_HOSTILE || !nationRelation->should_attack )
				return 0;
      }
		else if(!townPtr->is_hostile_nation(nation_recno))
			return 0;
   }
   else if(!independent_nation_can_attack(targetNationRecno))
      return 0;

   if(space_for_attack(townPtr->loc_x1, townPtr->loc_y1, UNIT_LAND, STD_TOWN_LOC_WIDTH, STD_TOWN_LOC_HEIGHT))
      return 1;
   else
      return 0;
}
