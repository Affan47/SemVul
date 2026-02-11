open_south_gate(short x1, short y1, short townRecno)
{

	Location *locPtr = get_loc(x1+2,y1);
	if( locPtr->is_wall() && locPtr->wall_id() == SGATE_W &&
		locPtr->wall_town_recno() == townRecno)
	{
		for(short x = 3; x < GATE_LENGTH-3; ++x)
			for(short y = 0; y < GATE_WIDTH; ++y)
				get_loc(x1+x, y1+y)->remove_wall();

	}
}
