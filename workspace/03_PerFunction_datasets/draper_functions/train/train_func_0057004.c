disp_ranking()
{


	int x=20, y=76;

	font_bible.put( x+20 , y+7, "Kingdom" );
	font_bible.put( x+260, y+7, "Population" );
	font_bible.put( x+370, y+7, "Military" );
	font_bible.put( x+470, y+7, "Economy" );
	font_bible.put( x+562, y+7, "Reputation" );

#if(defined(SPANISH))
	font_bible.put( x+670, y   , "Lucha" );
	font_bible.put( x+670, y+14, "Fryhtan" );
#else
	font_bible.put( x+670, y   , "Fryhtan" );
	font_bible.put( x+670, y+14, "Battling" );
#endif


	put_ranking(y+=36, nation_array.player_recno);

	for( int i=1 ; i<=nation_array.size() ; i++ )
	{
		if( nation_array.is_deleted(i) || i==nation_array.player_recno )
			continue;

		put_ranking( y+=30, i );
	}
}
