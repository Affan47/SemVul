date2isoweek(int year, int mon, int mday)
{
	float8		result;
	int			day0,
				day4,
				dayn;


	dayn = date2j(year, mon, mday);


	day4 = date2j(year, 1, 4);


	day0 = j2day(day4 - 1);


	if (dayn < day4 - day0)
	{
		day4 = date2j(year - 1, 1, 4);


		day0 = j2day(day4 - 1);
	}

	result = (dayn - (day4 - day0)) / 7 + 1;


	if (result >= 52)
	{
		day4 = date2j(year + 1, 1, 4);


		day0 = j2day(day4 - 1);

		if (dayn >= day4 - day0)
			result = (dayn - (day4 - day0)) / 7 + 1;
	}

	return (int) result;
}
