put_town_rec(int recNo, int x, int y, int refreshFlag)
{
	int   townRecno = town_filter(recNo);
	Town* townPtr   = town_array[townRecno];


	x+=3;
	y+=3;

	font_san.put( x    , y, townPtr->town_name() );
	font_san.put( x+175, y, townPtr->population );
	font_san.put( x+241, y, townPtr->jobless_population );
	font_san.put( x+309, y, townPtr->average_loyalty() );


	x += 350;

	int i;
	int iconSpacing = RACE_ICON_WIDTH+2;
#if(MAX_RACE > 7)
	int raceCount = 0;
	for( i=0 ; i<MAX_RACE ; i++ )
	{
		if( townPtr->race_pop_array[i] > 0 )
		{
			++raceCount;
		}
	}
	if( raceCount > 7 )
	{
		iconSpacing = 7 * iconSpacing / raceCount;
	}
#endif
	for( i=0 ; i<MAX_RACE ; i++ )
	{
		if( townPtr->race_pop_array[i] > 0 )
		{
			vga_back.put_bitmap( x, y-2, race_res[i+1]->icon_bitmap_ptr );
			x += iconSpacing;
		}
	}
}
