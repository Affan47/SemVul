perlAuthInit(void)
{
    dSP;
    int rc;

    if (!PerlFilterActive)
        return;

    if (perl_get_cv("auth_init", 0) == NULL) {
        return;
    }

    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    PUTBACK;

    rc = perl_call_pv("auth_init", G_EVAL|G_DISCARD);

    SPAGAIN;

    if (SvTRUE(ERRSV)) {
        syslog(L_ERROR, "Perl function authenticate died: %s",
               SvPV(ERRSV, PL_na));
        Reply("%d Internal error (1).  Goodbye!\r\n", NNTP_FAIL_TERMINATING);
        ExitWithStats(1, true);
    }

    while (rc--) {
        (void)POPs;
    }

    PUTBACK;
    FREETMPS;
    LEAVE;
}
