assign_random_seed(double newval, void *extra)
{

	if (*((int *) extra))
		DirectFunctionCall1(setseed, Float8GetDatum(newval));
	*((int *) extra) = 0;
}
