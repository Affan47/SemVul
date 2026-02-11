THX_run_cleanup(pTHX_ void *cleanup_code_ref)
{
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    call_sv((SV*)cleanup_code_ref, G_VOID|G_DISCARD);
    FREETMPS;
    LEAVE;
}
