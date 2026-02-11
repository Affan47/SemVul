ran_normal_box_muller (void)
{
    double x, y, z;

 tryagain:
    x = gretl_rand_01();
    y = gretl_rand_01();
    z = sqrt(-2. * log(x));

    if (isnan(z) || isinf(z)) {
	goto tryagain;
    }

    return z * cos(M_2PI * y);
}
