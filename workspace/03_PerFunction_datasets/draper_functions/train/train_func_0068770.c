l_intvl(double u, double lambda)
{


    if (u==0) {
	return false;
    }
    if (lambda < 1E-3) {
	return false;
    }

    double h = 0.5*log(2.0) + 2.5*log(PI) - 2.5*log(lambda) -
	PI_SQUARE/(2 * lambda) + 0.5*lambda;
    double logu = log(u);
    double z = 1;
    double x = exp(-PI_SQUARE/(2*lambda));
    double k = lambda / PI_SQUARE;
    int j = 0;
    while(true) {
	j++;
	z -= k*pow(x, j*j-1);
	if (h + log(z) > logu)
	    return true;
	j++;
	int j2 = (j+1)*(j+1);
	z += j2*pow(x,j2-1);
	if (h + log(z) < logu)
	    return false;
    }
}
