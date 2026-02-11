getInitialDateByType( uint type )
{
	switch(type) {
		case 0:
			return _startday;
			break;
		case 1:
			return _startdaynum;
			break;
		case 2:
			return _startweek;
			break;
		case 3:
			return _startmonth;
			break;
		case 4:
			return _startyear;
			break;
		default:
			logEE( "Error, unknow type of date" );
			return _startday;
			break;
	}


}
