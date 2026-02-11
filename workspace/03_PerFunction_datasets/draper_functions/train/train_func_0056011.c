deinit_unit_mode()
{
	if( sys.signal_exit_flag )
		return;


   if(unit_mode==UNIT_MODE_DEFEND_TOWN)
   {
      if(!town_array.is_deleted(unit_mode_para))
      {
         Town *townPtr = town_array[unit_mode_para];

         if(nation_recno == townPtr->nation_recno)
            townPtr->reduce_defender_count();
      }
      set_mode(0);
   }


	else if( unit_mode==UNIT_MODE_MONSTER && unit_mode_para )
	{
		if(((UnitMonster*)this)->monster_action_mode!=MONSTER_ACTION_DEFENSE)
			return;

		FirmMonster* firmMonster = (FirmMonster*) firm_array[unit_mode_para];

		err_when( firmMonster->firm_id != FIRM_MONSTER );

		firmMonster->reduce_defender_count(rank_id);
	}
}
