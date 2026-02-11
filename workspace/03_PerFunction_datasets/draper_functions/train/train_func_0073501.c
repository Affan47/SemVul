auto_spectrum_order (int T, gretlopt opt)
{
    int m;

    if (opt & OPT_O) {

	m = (int) 2.0 * sqrt((double) T);
    } else {

	double m1 = floor((double) T / 2.0);
	double m2 = floor(pow((double) T, 0.6));

	m = (m1 < m2)? m1 : m2;
	m--;
    }

    return m;
}
