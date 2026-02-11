my_isnan(dtype_t type, void *val)
{
    hbool_t retval = FALSE;
    char s[256];

    if (FLT_FLOAT==type)
    {
        float x;

        HDmemcpy(&x, val, sizeof(float));
        retval = (x!=x);
    }
    else if (FLT_DOUBLE==type)
    {
        double x;

        HDmemcpy(&x, val, sizeof(double));
        retval = (x!=x);
    }
#if H5_SIZEOF_LONG_DOUBLE!=H5_SIZEOF_DOUBLE && H5_SIZEOF_LONG_DOUBLE!=0
    else if (FLT_LDOUBLE==type)
    {
        long double x;

        HDmemcpy(&x, val, sizeof(long double));
        retval = (x!=x);
    }
#endif
    else
    {
        return FALSE;
    }


    if (!retval)
    {
        if (FLT_FLOAT==type)
        {
            float x;

            HDmemcpy(&x, val, sizeof(float));
            HDsnprintf(s, sizeof(s), "%g", (double)x);
        }
        else if (FLT_DOUBLE==type)
        {
            double x;

            HDmemcpy(&x, val, sizeof(double));
            HDsnprintf(s, sizeof(s), "%g", x);
        }
#if H5_SIZEOF_LONG_DOUBLE!=H5_SIZEOF_DOUBLE && H5_SIZEOF_LONG_DOUBLE!=0
        else if (FLT_LDOUBLE==type)
        {
            long double x;

            HDmemcpy(&x, val, sizeof(long double));
            HDsnprintf(s, sizeof(s), "%Lg", x);
        }
#endif
        else
        {
            return FALSE;
        }

        if ( HDstrstr(s, "NaN") ||
             HDstrstr(s, "NAN") ||
             HDstrstr(s, "nan") ||
             HDstrstr(s, "-1.#IND")
           )
        {
            retval = TRUE;
        }
    }

#ifdef H5_VMS


    if(!retval)
    {
        if (FLT_FLOAT==type)
        {
            float x;

            HDmemcpy(&x, val, sizeof(float));
            retval = (x==FLT_MAX || x==-FLT_MAX);
        } else if (FLT_DOUBLE==type) {
            double x;

            HDmemcpy(&x, val, sizeof(double));
            retval = (x==DBL_MAX || x==-DBL_MAX);
        } else
        {
            return FALSE;
        }
    }
#endif

    return retval;
}
