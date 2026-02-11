think_marine()
{
	if( pref_use_marine < 50 )
		return;

	if( !ai_should_spend(20+pref_use_marine/2) )
		return;


	think_build_harbor_network();

	if( ai_harbor_count == 0 )
		return;


	if( misc.random(3)==0 )
	{
		if( think_sea_attack_enemy() )
			return;
	}


	if( !ai_is_sea_travel_safe() )
		return;


	think_move_between_region();


}
