fminf(float x, float y)
{

	if (isnan(x))
		return (y);
	if (isnan(y))
		return (x);


	if (signbit(x) != signbit(y))
		if (signbit(y))
			return (y);
		else
			return (x);

	return (x < y ? x : y);
}
