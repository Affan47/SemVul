cpl_column_absolute(cpl_column *column)
{

    const char *fid  = "cpl_column_absolute";
    cpl_type    type = cpl_column_get_type(column);
    cpl_size    length;
    cpl_size    nullcount;
    cpl_size    i;


    if (column == 0x0)
        return cpl_error_set(fid, CPL_ERROR_NULL_INPUT);

    switch (type) {
    case CPL_TYPE_INT:
        break;
    case CPL_TYPE_LONG:
        break;
    case CPL_TYPE_LONG_LONG:
        break;
    case CPL_TYPE_FLOAT:
        break;
    case CPL_TYPE_DOUBLE:
        break;
    default:
        return cpl_error_set(fid, CPL_ERROR_INVALID_TYPE);
    }

    length    = cpl_column_get_size(column);
    nullcount = cpl_column_count_invalid(column);

    if (nullcount == length)
        return CPL_ERROR_NONE;

    switch (type) {

    case CPL_TYPE_INT:
    {
        int *ip = cpl_column_get_data_int(column);
        for (i = 0; i < length; i++, ip++)
            *ip = abs(*ip);
        break;
    }
    case CPL_TYPE_LONG:
    {
        long *lp = cpl_column_get_data_long(column);
        for (i = 0; i < length; i++, lp++)
            *lp = labs(*lp);
        break;
    }
    case CPL_TYPE_LONG_LONG:
    {
        long long *lp = cpl_column_get_data_long_long(column);

#if defined(HAVE_LLABS) && defined(HAVE_DECL_LLABS)

        for (i = 0; i < length; i++, lp++)
            *lp = llabs(*lp);

#else

        for (i = 0; i < length; i++, lp++)
            *lp = *lp < 0LL ? -(*lp) : *lp;

#endif

        break;
    }
    case CPL_TYPE_SIZE:
    {
        cpl_size *lp = cpl_column_get_data_cplsize(column);

#if defined(HAVE_LLABS) && defined(HAVE_DECL_LLABS)

        for (i = 0; i < length; i++, lp++)
            *lp = llabs(*lp);

#else

        for (i = 0; i < length; i++, lp++)
            *lp = *lp < 0LL ? -(*lp) : *lp;

#endif

        break;
    }
    case CPL_TYPE_FLOAT:
    {
        float *fp = cpl_column_get_data_float(column);
        for (i = 0; i < length; i++, fp++)
            *fp = fabsf(*fp);
        break;
    }
    case CPL_TYPE_DOUBLE:
    {
        double *dp = cpl_column_get_data_double(column);
        for (i = 0; i < length; i++, dp++)
            *dp = fabs(*dp);
        break;
    }
    default:
        return cpl_error_set(fid, CPL_ERROR_INVALID_TYPE);

    }

    return CPL_ERROR_NONE;

}
