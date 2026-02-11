is_rt_mappable(wchar_t c, CCharmapToLocal *to_local,
                                  CCharmapToUni *to_uni)
{
    char lclbuf[16];
    char unibuf[16];
    size_t lcllen;
    size_t unilen;
    char *p;


    if (!to_local->is_mappable(c))
        return FALSE;


    if (to_local->get_expansion(c, &lcllen) != 0)
        return FALSE;


    lcllen = to_local->map_char(c, lclbuf, sizeof(lclbuf));


    p = unibuf;
    unilen = sizeof(unibuf);
    unilen = to_uni->map(&p, &unilen, lclbuf, lcllen);


    return (unilen == utf8_ptr::s_wchar_size(c)
            && utf8_ptr::s_getch(unibuf) == c);
}
