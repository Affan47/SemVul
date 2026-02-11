ry1(double x)
{
    if (x <= 0.0)
	return (dzero / dzero);
    if (x < 8.0)
	return (x * yone(x) + TWO_ON_PI * (rj1(x) * log(x) - 1.0 / x));
    else
	return (sqrt(TWO_ON_PI / x) *
		(pone(x) * sin(x - THREE_PI_ON_FOUR) +
		 (8.0 / x) * qone(x) * cos(x - THREE_PI_ON_FOUR)));
}
