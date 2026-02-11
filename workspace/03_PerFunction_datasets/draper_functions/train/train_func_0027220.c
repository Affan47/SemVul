run_app(request_rec *r, SV *app, SV *env)
{
    dTHX;
    int count;
    SV *res;
    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP) ;
    XPUSHs(sv_2mortal(env));
    PUTBACK;

    count = call_sv(app, G_EVAL|G_SCALAR|G_KEEPERR);
    SPAGAIN;
    if (SvTRUE(ERRSV)) {
        res = NULL;
        server_error(r, "%s", SvPV_nolen(ERRSV));
        CLEAR_ERRSV();
        (void) POPs;
    } else if (count > 0) {
        res = POPs;
        SvREFCNT_inc(res);
    } else {
        res = NULL;
    }
    PUTBACK;
    FREETMPS;
    LEAVE;
    return res;
}
