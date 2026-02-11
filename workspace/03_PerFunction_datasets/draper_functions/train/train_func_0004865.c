m_tgamma(double x)
{
    double absx, r, y, z, sqrtpow;


    if (!Py_IS_FINITE(x)) {
        if (Py_IS_NAN(x) || x > 0.0)
            return x;
        else {
            errno = EDOM;
            return Py_NAN;
        }
    }
    if (x == 0.0) {
        errno = EDOM;
        return 1.0/x;
    }


    if (x == floor(x)) {
        if (x < 0.0) {
            errno = EDOM;
            return Py_NAN;
        }
        if (x <= NGAMMA_INTEGRAL)
            return gamma_integral[(int)x - 1];
    }
    absx = fabs(x);


    if (absx < 1e-20) {
        r = 1.0/x;
        if (Py_IS_INFINITY(r))
            errno = ERANGE;
        return r;
    }


    if (absx > 200.0) {
        if (x < 0.0) {
            return 0.0/sinpi(x);
        }
        else {
            errno = ERANGE;
            return Py_HUGE_VAL;
        }
    }

    y = absx + lanczos_g_minus_half;

    if (absx > lanczos_g_minus_half) {


        double q = y - absx;
        z = q - lanczos_g_minus_half;
    }
    else {
        double q = y - lanczos_g_minus_half;
        z = q - absx;
    }
    z = z * lanczos_g / y;
    if (x < 0.0) {
        r = -pi / sinpi(absx) / absx * exp(y) / lanczos_sum(absx);
        r -= z * r;
        if (absx < 140.0) {
            r /= pow(y, absx - 0.5);
        }
        else {
            sqrtpow = pow(y, absx / 2.0 - 0.25);
            r /= sqrtpow;
            r /= sqrtpow;
        }
    }
    else {
        r = lanczos_sum(absx) / exp(y);
        r += z * r;
        if (absx < 140.0) {
            r *= pow(y, absx - 0.5);
        }
        else {
            sqrtpow = pow(y, absx / 2.0 - 0.25);
            r *= sqrtpow;
            r *= sqrtpow;
        }
    }
    if (Py_IS_INFINITY(r))
        errno = ERANGE;
    return r;
}
