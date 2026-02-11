c_exp(Py_complex z)
{
    Py_complex r;
    double l;

    if (!Py_IS_FINITE(z.real) || !Py_IS_FINITE(z.imag)) {
        if (Py_IS_INFINITY(z.real) && Py_IS_FINITE(z.imag)
            && (z.imag != 0.)) {
            if (z.real > 0) {
                r.real = copysign(INF, cos(z.imag));
                r.imag = copysign(INF, sin(z.imag));
            }
            else {
                r.real = copysign(0., cos(z.imag));
                r.imag = copysign(0., sin(z.imag));
            }
        }
        else {
            r = exp_special_values[special_type(z.real)]
                                  [special_type(z.imag)];
        }


        if (Py_IS_INFINITY(z.imag) &&
            (Py_IS_FINITE(z.real) ||
             (Py_IS_INFINITY(z.real) && z.real > 0)))
            errno = EDOM;
        else
            errno = 0;
        return r;
    }

    if (z.real > CM_LOG_LARGE_DOUBLE) {
        l = exp(z.real-1.);
        r.real = l*cos(z.imag)*Py_MATH_E;
        r.imag = l*sin(z.imag)*Py_MATH_E;
    } else {
        l = exp(z.real);
        r.real = l*cos(z.imag);
        r.imag = l*sin(z.imag);
    }

    if (Py_IS_INFINITY(r.real) || Py_IS_INFINITY(r.imag))
        errno = ERANGE;
    else
        errno = 0;
    return r;
}
