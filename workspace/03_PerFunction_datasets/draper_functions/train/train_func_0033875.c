resign(int remoteAction)
{
   if( !remoteAction && remote.is_enable() )
   {

      short *shortPtr = (short *)remote.new_send_queue_msg(MSG_UNIT_RESIGN, 2*sizeof(short));
      *shortPtr = sprite_recno;
		shortPtr[1] = nation_array.player_recno;

      return;
   }


   if( race_id )
		town_array.race_wander_pop_array[race_id-1] += 2;


	if( is_visible() )
		stop2();


	if( spy_recno && true_nation_recno() != nation_recno )
	{


		nation_array[true_nation_recno()]->change_reputation((float)-SPY_KILLED_REPUTATION_DECREASE);


		if( true_nation_recno() == nation_array.player_recno ||
			 nation_recno == nation_array.player_recno )
		{


			news_array.spy_killed(spy_recno);
		}
	}


	if( rank_id == RANK_GENERAL )
		news_array.news_add_flag=0;

	unit_array.del( sprite_recno );

	news_array.news_add_flag=1;
}
