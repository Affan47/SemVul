spy_change_nation(int newNationRecno, char remoteAction)
{
	if( newNationRecno == nation_recno )
		return;

	if( newNationRecno && nation_array.is_deleted(newNationRecno) )
		return;


	if( !remoteAction && remote.is_enable() )
	{

		short *shortPtr = (short *)remote.new_send_queue_msg(MSG_UNIT_SPY_NATION, 2*sizeof(short) );
		*shortPtr = sprite_recno;
		shortPtr[1] = newNationRecno;
		return;
	}


	Spy* spyPtr = spy_array[spy_recno];


	if( is_visible() &&
		 rank_id == RANK_GENERAL &&
		 newNationRecno != spyPtr->true_nation_recno )
	{
		set_rank(RANK_SOLDIER);
	}


	if( spyPtr->true_nation_recno != nation_array.player_recno )
	{
		if( rank_id == RANK_GENERAL || unit_mode == UNIT_MODE_OVERSEE ||
			 spyPtr->notify_cloaked_nation_flag )
		{


			if( nation_recno == nation_array.player_recno )
				news_array.unit_betray(sprite_recno, newNationRecno);
		}


		if( spyPtr->notify_cloaked_nation_flag )
		{
			if( newNationRecno == nation_array.player_recno )
				news_array.unit_betray(sprite_recno, newNationRecno);
		}
	}


	spyPtr->cloaked_nation_recno = newNationRecno;

	betray(newNationRecno);
}
