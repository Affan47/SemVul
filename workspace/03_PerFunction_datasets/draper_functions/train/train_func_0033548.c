gig(double delta, RNG *rng)
{


    double y = rng->normal();
    y = y * y;
    if (delta <= 1.0E-6 * y) {

	return y;
    }
    else {
	y = 1 + (y - sqrt(y * (4*delta + y))) / (2*delta);
	return (rng->uniform() <= 1/(1 + y)) ? delta/y : delta*y;
    }
}
