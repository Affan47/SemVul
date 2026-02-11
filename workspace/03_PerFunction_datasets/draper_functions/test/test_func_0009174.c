testStatics()
{
	assert (DateTime::isLeapYear(1984));
	assert (DateTime::isLeapYear(1988));
	assert (DateTime::isLeapYear(1992));
	assert (DateTime::isLeapYear(1996));
	assert (DateTime::isLeapYear(2000));
	assert (DateTime::isLeapYear(2400));
	assert (!DateTime::isLeapYear(1995));
	assert (!DateTime::isLeapYear(1998));
	assert (!DateTime::isLeapYear(2001));
	assert (!DateTime::isLeapYear(1800));
	assert (!DateTime::isLeapYear(1900));

	assert (DateTime::daysOfMonth(2000, 1) == 31);
	assert (DateTime::daysOfMonth(2000, 2) == 29);
	assert (DateTime::daysOfMonth(1999, 2) == 28);
}
