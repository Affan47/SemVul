detect_worker_list()
{
	if( !should_show_info() )
		return 0;


	int i, x, y;
	int liveInTown = firm_res[firm_id]->live_in_town;

	for( i=0 ; i<worker_count ; i++ )
	{
		x = INFO_X1+6+i%4*50;
		y = pop_disp_y1+1+i/4*29;

		switch( mouse.single_click(x, y, x+27, y+23, 2) )
		{
			case 1:
				selected_worker_id = i+1;
				return 1;

			case 2:
				if( own_firm() )
				{


					mobilize_worker(i+1, COMMAND_PLAYER);
					return 1;
				}
				break;
		}
	}

	return 0;
}
