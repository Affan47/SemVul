okayvalue(value)
of_t value;
{
	if (HASTAG(value))
		return(0);
#ifdef OVERFLOW
	if (value == LONG_MAX)
		return(0);
#endif
	return(1);
}
