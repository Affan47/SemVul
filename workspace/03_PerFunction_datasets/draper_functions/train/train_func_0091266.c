ap_ht_time(apr_pool_t *p, apr_time_t t, const char *fmt,
                              int gmt)
{
    apr_size_t retcode;
    char ts[MAX_STRING_LEN];
    char tf[MAX_STRING_LEN];
    apr_time_exp_t xt;

    if (gmt) {
        const char *f;
        char *strp;

        apr_time_exp_gmt(&xt, t);


        for(strp = tf, f = fmt; strp < tf + sizeof(tf) - 6 && (*strp = *f)
            ; f++, strp++) {
            if (*f != '%') continue;
            switch (f[1]) {
            case '%':
                *++strp = *++f;
                break;
            case 'Z':
                *strp++ = 'G';
                *strp++ = 'M';
                *strp = 'T';
                f++;
                break;
            case 'z':
                *strp++ = '+';
                *strp++ = '0';
                *strp++ = '0';
                *strp++ = '0';
                *strp = '0';
                f++;
                break;
            }
        }
        *strp = '\0';
        fmt = tf;
    }
    else {
        apr_time_exp_lt(&xt, t);
    }


    apr_strftime(ts, &retcode, MAX_STRING_LEN, fmt, &xt);
    ts[MAX_STRING_LEN - 1] = '\0';
    return apr_pstrdup(p, ts);
}
