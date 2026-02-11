subtract(count_t newval, count_t oldval)
{
	if (newval >= oldval)
		return (double) newval - oldval;
	else
		return (double) ULONG_MAX + 1.0 + newval - oldval;
}
