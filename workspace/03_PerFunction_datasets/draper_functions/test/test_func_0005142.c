S_check_type_and_open(pTHX_ SV *name)
{
    Stat_t st;
    const char *p = SvPV_nolen_const(name);
    const int st_rc = PerlLIO_stat(p, &st);

    PERL_ARGS_ASSERT_CHECK_TYPE_AND_OPEN;

    if (st_rc < 0 || S_ISDIR(st.st_mode) || S_ISBLK(st.st_mode)) {
	return NULL;
    }

#if !defined(PERLIO_IS_STDIO) && !defined(USE_SFIO)
    return PerlIO_openn(aTHX_ ":", PERL_SCRIPT_MODE, -1, 0, 0, NULL, 1, &name);
#else
    return PerlIO_open(p, PERL_SCRIPT_MODE);
#endif
}
