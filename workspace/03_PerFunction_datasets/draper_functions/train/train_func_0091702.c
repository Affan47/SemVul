fill_week_days(Request& r, MethodParams& params, bool rus){
	Table::columns_type columns(new ArrayString(4));
	*columns+=new String("year");
	*columns+=new String("month");
	*columns+=new String("day");
	*columns+=new String("weekday");
	Table& result=*new Table(columns);

	int year=to_year(params.as_int(1, "year must be int", r));
	int month=to_month(params.as_int(2, "month must be int", r));
	int day=params.as_int(3, "day must be int", r);

	tm tmIn;
	memset(&tmIn, 0, sizeof(tmIn));
	tmIn.tm_hour=18;
	tmIn.tm_mday=day;
	tmIn.tm_mon=month;
	tmIn.tm_year=year-1900;

	time_t t=mktime(&tmIn);
	if(t<0)
		throw Exception(DATE_RANGE_EXCEPTION_TYPE,
			0,
			"invalid date");
	tm *tmOut=localtime(&t);

	int baseWeekDay=tmOut->tm_wday;
	if(rus)
		baseWeekDay=baseWeekDay?baseWeekDay-1:6;

	t-=baseWeekDay*SECS_PER_DAY;

	for(int curWeekDay=0; curWeekDay<7; curWeekDay++, t+=SECS_PER_DAY) {
		tm *tmOut=localtime(&t);
		Table::element_type row(new ArrayString(4));

		*row+=new String(1900+tmOut->tm_year, "%04d");
		*row+=new String(1+tmOut->tm_mon, "%02d");
		*row+=new String(tmOut->tm_mday, "%02d");
		*row+=new String(tmOut->tm_wday, "%02d");

		result+=row;
	}

	return result;
}
