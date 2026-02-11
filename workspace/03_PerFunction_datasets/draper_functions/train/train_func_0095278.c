is_valid_to_disp()
{


	if( nation_array.is_deleted(from_nation_recno) )
		return 0;

	if( nation_array.is_deleted(to_nation_recno) )
		return 0;


	Nation* toNation   = nation_array[to_nation_recno];
	Nation* fromNation = nation_array[from_nation_recno];

	switch( talk_id )
	{
		case TALK_REQUEST_TRADE_EMBARGO:
			if( nation_array.is_deleted(talk_para1) )
				return 0;
			break;

		case TALK_REQUEST_DECLARE_WAR:
			if( nation_array.is_deleted(talk_para1) )
				return 0;
			break;
	}

	return 1;
}
