is_leap_year (IV y)
{
	return (y % 4 == 0) && ((y % 100 != 0) || (y % 400 == 0));
}
