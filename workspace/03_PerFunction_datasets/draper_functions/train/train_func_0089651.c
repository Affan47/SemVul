cprojf(float complex z)
{

	if (!isinf(crealf(z)) && !isinf(cimagf(z)))
		return (z);
	else
		return (cpackf(INFINITY, copysignf(0.0, cimagf(z))));
}
