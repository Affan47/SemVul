date2dos(time_t t)
{
	struct tm *x;
	x = localtime (&t);
	D2(bug("HOSTFS: date2dos (%d,%d,%d)", x->tm_mday, x->tm_mon, x->tm_year-80+1980));
	return x->tm_mday|((x->tm_mon+1)<<5)|(MAX(x->tm_year-80,0)<<9);
}
