setboundaries(void)
{


	min_time = ~(pg_time_t) 0;
	min_time <<= TYPE_BIT(pg_time_t) -1;
	max_time = ~(pg_time_t) 0 - min_time;


	min_time = Max(min_time, (pg_time_t) INT_MIN);
	max_time = Min(max_time, (pg_time_t) INT_MAX);

	min_year = TM_YEAR_BASE + pg_gmtime(&min_time)->tm_year;
	max_year = TM_YEAR_BASE + pg_gmtime(&max_time)->tm_year;
	min_year_representable = min_year;
	max_year_representable = max_year;
}
