ves_icall_System_Math_Asin (gdouble x)
{
	if (x < -1 || x > 1)
		return NaN.d;

	return asin (x);
}
