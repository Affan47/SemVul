validate_cur_bribe()
{
	if( spy_array.is_deleted(action_spy_recno) ||
		 spy_array[action_spy_recno]->true_nation_recno != nation_array.player_recno )
	{
		return 0;
	}

	return can_spy_bribe( selected_worker_id, spy_array[action_spy_recno]->true_nation_recno );
}
