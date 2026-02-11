Perl_grok_numeric_radix(pTHX_ const char **sp, const char *send)
{
#ifdef USE_LOCALE_NUMERIC
    dVAR;

    PERL_ARGS_ASSERT_GROK_NUMERIC_RADIX;

    if (PL_numeric_radix_sv && IN_SOME_LOCALE_FORM) {
        STRLEN len;
        const char * const radix = SvPV(PL_numeric_radix_sv, len);
        if (*sp + len <= send && memEQ(*sp, radix, len)) {
            *sp += len;
            return TRUE;
        }
    }


#endif

    PERL_ARGS_ASSERT_GROK_NUMERIC_RADIX;

    if (*sp < send && **sp == '.') {
        ++*sp;
        return TRUE;
    }
    return FALSE;
}
