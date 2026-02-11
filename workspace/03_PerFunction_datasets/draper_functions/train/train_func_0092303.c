getCost( uint res )
{
	uint ret = 0;

	if( (int)res < DataTheme.resources.count() ) {
		ret = _cost[res];
	}

	return ret;
}
