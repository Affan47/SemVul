gym_track_length( byte const* p, byte const* end )
{
	long time = 0;
	while ( p < end )
	{
		switch ( *p++ )
		{
			case 0:
				time++;
				break;

			case 1:
			case 2:
				p += 2;
				break;

			case 3:
				p += 1;
				break;
		}
	}
	return time;
}
