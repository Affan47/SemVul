_yconv(const int a, const int b, const int convert_top,
	   const int convert_yy, char *pt, const char *const ptlim)
{
	int			lead;
	int			trail;

#define DIVISOR		  100
	trail = a % DIVISOR + b % DIVISOR;
	lead = a / DIVISOR + b / DIVISOR + trail / DIVISOR;
	trail %= DIVISOR;
	if (trail < 0 && lead > 0)
	{
		trail += DIVISOR;
		--lead;
	}
	else if (lead < 0 && trail > 0)
	{
		trail -= DIVISOR;
		++lead;
	}
	if (convert_top)
	{
		if (lead == 0 && trail < 0)
			pt = _add("-0", pt, ptlim);
		else
			pt = _conv(lead, "%02d", pt, ptlim);
	}
	if (convert_yy)
		pt = _conv(((trail < 0) ? -trail : trail), "%02d", pt, ptlim);
	return pt;
}
