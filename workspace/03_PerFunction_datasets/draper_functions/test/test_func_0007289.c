close_trace_file(pTHX)
{
    dMY_CXT;
    if (DBILOGFP == PerlIO_stderr() || DBILOGFP == PerlIO_stdout())
        return;

    if (DBIS->logfp_ref == NULL)
        PerlIO_close(DBILOGFP);
    else {

        SvREFCNT_dec(DBIS->logfp_ref);
        DBIS->logfp_ref = NULL;
    }
}
