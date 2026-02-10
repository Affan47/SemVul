ai_is_troop_need_new_camp()
{


	if( ai_has_too_many_camp() )
		return 0;


	if( !ai_should_spend(50+pref_military_development/2) )
		return 0;


	int neededSoldierSpace = total_human_count+total_weapon_count - ai_camp_count*MAX_WORKER;
	int neededGeneralSpace = total_general_count - ai_camp_count;

	return neededSoldierSpace >= 9 + 20 * (100-pref_military_development) / 200 &&
			 neededGeneralSpace >= 2 + 4  * (100-pref_military_development) / 200;
}
