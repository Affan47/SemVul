testSORTABLE()
{
	int tzd;
	DateTime dt = DateTimeParser::parse(DateTimeFormat::SORTABLE_FORMAT, "2005-01-08 12:30:00", tzd);
	assert (dt.year() == 2005);
	assert (dt.month() == 1);
	assert (dt.day() == 8);
	assert (dt.hour() == 12);
	assert (dt.minute() == 30);
	assert (dt.second() == 0);
	assert (tzd == 0);

	dt = DateTimeParser::parse(DateTimeFormat::SORTABLE_FORMAT, "2005-01-08", tzd);
	assert (dt.year() == 2005);
	assert (dt.month() == 1);
	assert (dt.day() == 8);
	assert (dt.hour() == 0);
	assert (dt.minute() == 0);
	assert (dt.second() == 0);
	assert (tzd == 0);
}
