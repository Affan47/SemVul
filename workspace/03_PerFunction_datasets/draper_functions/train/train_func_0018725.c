_g_date_time_same_day (GDateTime *dt1,
		       GDateTime *dt2)
{
	int y1, m1, d1;
	int y2, m2, d2;

	g_date_time_get_ymd (dt1, &y1, &m1, &d1);
	g_date_time_get_ymd (dt2, &y2, &m2, &d2);

	return (y1 == y2) && (m1 == m2) && (d1 == d2);
}
