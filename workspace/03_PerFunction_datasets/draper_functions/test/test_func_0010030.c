umf_hypot (double x, double y)
{
    double s, r ;
    x = SCALAR_ABS (x) ;
    y = SCALAR_ABS (y) ;
    if (x >= y)
    {
	if (x + y == x)
	{
	    s = x ;
	}
	else
	{
	    r = y / x ;
	    s = x * sqrt (1.0 + r*r) ;
	}
    }
    else
    {
	if (y + x == y)
	{
	    s = y ;
	}
	else
	{
	    r = x / y ;
	    s = y * sqrt (1.0 + r*r) ;
	}
    }
    return (s) ;
}
