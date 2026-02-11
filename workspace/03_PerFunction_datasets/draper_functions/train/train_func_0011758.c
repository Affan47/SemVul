flo_is_finite_p(VALUE num)
{
    double value = RFLOAT_VALUE(num);

#if HAVE_FINITE
    if (!finite(value))
	return Qfalse;
#else
    if (isinf(value) || isnan(value))
	return Qfalse;
#endif

    return Qtrue;
}
