Scm_HalfToDouble(ScmHalfFloat v)
{
    int e = SCM_HALF_FLOAT_EXPONENT(v);
    int m = SCM_HALF_FLOAT_MANTISSA(v);
    int s = SCM_HALF_FLOAT_SIGN_BIT(v);
    if (e == 31) {
        if (m == 0) {
            if (s) return SCM_DBL_NEGATIVE_INFINITY;
            else   return SCM_DBL_POSITIVE_INFINITY;
        } else {
            return SCM_DBL_NAN;
        }
    }
    if (e > 0) {
        double d = ldexp(1.0 + m/1024.0, e - 15);
        return s? -d : d;
    }
    else {
        double d = ldexp(m/1024.0, -14);
        return s? -d : d;
    }
}
