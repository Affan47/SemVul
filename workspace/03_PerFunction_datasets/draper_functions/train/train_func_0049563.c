getHashUInt(SV *opts, char *param, int def)
{
    SV **vp;

    if ( !opts || !SvROK(opts)
               || SvTYPE(SvRV(opts)) != SVt_PVHV
               || !(vp = hv_fetch((HV*)SvRV(opts), param, strlen(param), 0))
               || !*vp ) {
        return def;
    }
    return SvUV(*vp);
}
