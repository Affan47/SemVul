string_to_double(const char *str, double *result)
{
    char *endptr = 0x0;

    g_return_val_if_fail(str, FALSE);
    g_return_val_if_fail(result, FALSE);

    *result = strtod (str, &endptr);
    if (endptr == str) return (FALSE);

    return(TRUE);
}
