krb5_string_to_flags(string, positive, negative, flagsp)
    char        * string;
    const char  * positive;
    const char  * negative;
    krb5_flags  * flagsp;
{
    int         i;
    int         found;
    const char  *neg;
    size_t      nsize, psize;
    int         cpos;
    int         sense;

    found = 0;

    neg = (negative) ? negative : flags_default_neg;
    nsize = strlen(neg);
    psize = (positive) ? strlen(positive) : 0;

    cpos = 0;
    sense = 1;

    if (!strncasecmp(neg, string, nsize)) {
        sense = 0;
        cpos += (int) nsize;
    }
    else if (psize && !strncasecmp(positive, string, psize)) {
        cpos += (int) psize;
    }

    for (i=0; i<flags_table_nents; i++) {
        if (!strcasecmp(&string[cpos], flags_table[i].fl_specifier)) {
            found = 1;
            if (sense == (int) flags_table[i].fl_sense)
                *flagsp |= flags_table[i].fl_flags;
            else
                *flagsp &= ~flags_table[i].fl_flags;

            break;
        }
    }
    return((found) ? 0 : EINVAL);
}
