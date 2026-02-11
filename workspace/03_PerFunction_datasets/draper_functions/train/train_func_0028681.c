S_scan_word(pTHX_ char *s, char *dest, STRLEN destlen, int allow_package, STRLEN *slp)
{
    dVAR;
    char *d = dest;
    char * const e = d + destlen - 3;
    bool is_utf8 = cBOOL(UTF);

    PERL_ARGS_ASSERT_SCAN_WORD;

    parse_ident(&s, &d, e, allow_package, is_utf8);
    *d = '\0';
    *slp = d - dest;
    return s;
}
