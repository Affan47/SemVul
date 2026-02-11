game_duration_str()
{


	int gameStartDate;


	if( info.goal_difficulty )
	{
		gameStartDate =  date.julian( date.year(info.goal_deadline)-config.goal_year_limit,
							  date.month(info.goal_deadline),
							  date.day(info.goal_deadline) );
	}
	else
	{
		gameStartDate = info.game_start_date;
	}


	int totalDay = info.game_date - gameStartDate;
	int playYear = totalDay / 365;
	int playDay  = totalDay - playYear*365;

	static String str;

	str = "";

	if( playYear > 0 )
	{
		str += playYear;
		str += translate.process( playYear>1 ? (char*)" years" : (char*)" year" );
		str += translate.process( (char*)" and " );
	}

	str += playDay;
	str += translate.process( playDay>1  ? (char*)" days" : (char*)" day" );

	return str;
}
