m_log2(double x)
{
    if (!Py_IS_FINITE(x)) {
        if (Py_IS_NAN(x))
            return x;
        else if (x > 0.0)
            return x;
        else {
            errno = EDOM;
            return Py_NAN;
        }
    }

    if (x > 0.0) {
#ifdef HAVE_LOG2
        return log2(x);
#else
        double m;
        int e;
        m = frexp(x, &e);


        if (x >= 1.0) {
            return log(2.0 * m) / log(2.0) + (e - 1);
        }
        else {
            return log(m) / log(2.0) + e;
        }
#endif
    }
    else if (x == 0.0) {
        errno = EDOM;
        return -Py_HUGE_VAL;
    }
    else {
        errno = EDOM;
        return Py_NAN;
    }
}
