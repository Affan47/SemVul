HPDF_AToF  (const char  *s)
{
    HPDF_BOOL flg = HPDF_FALSE;
    HPDF_INT i = 0;
    HPDF_DOUBLE v;
    HPDF_INT tmp = 1;


    while (*s) {
        if (HPDF_IS_WHITE_SPACE(*s))
            s++;
        else {
            if (*s == '-') {
                flg = HPDF_TRUE;
                s++;
            }
            break;
        }
    }

    while (*s >= '0' && *s <= '9') {
        if (i > 3276)
            break;

        i *= 10;
        i += *s - '0';
        s++;
    }

    if (*s == '.') {
        s++;
        while (*s >= '0' && *s <= '9') {
            if (i > 214748364)
                break;

            i *= 10;
            i += *s - '0';
            s++;
            tmp *= 10;
        }
    }

    v = (HPDF_DOUBLE)i / tmp;

    if (flg)
        v *= -1;

    return v;
}
