Gauss_Rand(DBL c, DBL A, DBL S)
{
	DBL         y;

	y = (DBL) LRAND() / MAXRAND;
	y = A * (1.0 - exp(-y * y * S)) / (1.0 - exp(-S));
	if (NRAND(2))
		return (c + y);
	else
		return (c - y);
}
