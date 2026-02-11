PerlFMM_bufmagic(PerlFMM *self, SV *buf)
{
    unsigned char *buffer;
    char *type;
    int rc;
    SV *ret;


    if (SvROK(buf) && SvTYPE(SvRV(buf)) == SVt_PV) {
        buffer = (unsigned char *) SvPV_nolen( SvRV( buf ) );
    } else {
        buffer = (unsigned char *) SvPV_nolen(buf);
    }

    FMM_SET_ERROR(self, NULL);

    Newz(1234, type, BUFSIZ, char);

    rc = fmm_bufmagic(self, &buffer, &type);
    ret = FMM_RESULT(type, rc);
    Safefree(type);
    return ret;
}
