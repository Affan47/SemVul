m_var(double *data, int n, double *vari)
{
    double ave, ep, s;
    int i;

    if (n < 1) {
	G_warning(_("o_var: No data in array"));
	return (1);
    }

    *vari = 0.0;
    ep = 0;
    s = 0.0;


    for (i = 0; i < n; i++)
	s += data[i];
    ave = s / n;

    for (i = 0; i < n; i++) {
	s = data[i] - ave;

	*vari += s * s;
	ep += s;
    }

    *vari = (*vari - ep * ep / n) / (n - 1);

    return (0);
}
