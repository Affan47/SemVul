test_get_date (void)
{
	GckAttribute *attr;
	CK_DATE ck_date;
	GDate date, date2;

	g_date_set_dmy(&date, 05, 06, 1800);
	memcpy (ck_date.year, "1800", 4);
	memcpy (ck_date.month, "06", 2);
	memcpy (ck_date.day, "05", 2);
	attr = gck_attribute_new_date (ATTR_TYPE, &date);
	gck_attribute_get_date (attr, &date2);
	g_assert (g_date_compare (&date, &date2) == 0);
	gck_attribute_free (attr);
}
