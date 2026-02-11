normal_variate_pair(double *a, double *b) {


    double x, y, r2, m;

    do {
	x = uniform_variate();
	x += x - 1;
	y = uniform_variate();
	y += y - 1;


	r2 = x*x + y*y;
    } while (r2 > 1 || r2 == 0);


    m = sqrt(-2.0 * log(r2) / r2);
    *a = x * m;
    *b = y * m;
}
