parse_float(const char* s, double *value, const char **after)
{
    int neg_mant, neg_exp, digits, dot_exp, raw_exp;
    const char *after_dot;


    while (isspace(*s)) {
        s++;
    }


    if (*s == '-') {
       neg_mant = 1;
       s++;
    } else {
        neg_mant = 0;
    }


    digits = 0;
    *value = 0.0;
    while (isdigit(*s)) {
        *value = *value*10.0 + (*s++ - '0');
        digits++;
    }
    if (*s == '.') {
        after_dot = ++s;
        while (isdigit(*s)) {
            *value = *value*10.0 + (*s++ - '0');
            digits++;
        }
        dot_exp = after_dot - s;
    } else {
        dot_exp = 0;
    }
    if (digits == 0) {

        return EXIT_FAILURE;
    }


    raw_exp = 0;
    if (*s == 'e' || *s == 'E' || *s == 'd' || *s == 'D') {
        s++;
        if (*s == '-') {
            neg_exp = 1;
            s++;
        } else {
            neg_exp = 0;
            if (*s == '+') {
                s++;
            }
        }
        while (isdigit(*s)) {
            raw_exp = raw_exp*10 + (*s++ - '0');
        }
        if (neg_exp) {
            raw_exp = -raw_exp;
        }
    }


    *value = (neg_mant ? -(*value) : (*value)) * pow (10.0, dot_exp + raw_exp);

    if (after != NULL) {

        *after = s;
    }

    return EXIT_SUCCESS;

}
