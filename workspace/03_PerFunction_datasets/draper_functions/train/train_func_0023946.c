sharedsv_elem_mg_STORE(pTHX_ SV *sv, MAGIC *mg)
{
    dTHXc;
    SV *saggregate = SHAREDSV_FROM_OBJ(mg->mg_obj);
    SV **svp;
    U32 dualvar_flags = DUALVAR_FLAGS(sv);


    ENTER_LOCK;
    assert(saggregate);
    if (SvTYPE(saggregate) == SVt_PVAV) {
        assert ( mg->mg_ptr == 0 );
        SHARED_CONTEXT;
        svp = av_fetch((AV*) saggregate, mg->mg_len, 1);
    } else {
        char *key = mg->mg_ptr;
        I32 len = mg->mg_len;
        assert ( mg->mg_ptr != 0 );
        if (mg->mg_len == HEf_SVKEY) {
            STRLEN slen;
            key = SvPV((SV *)mg->mg_ptr, slen);
            len = slen;
            if (SvUTF8((SV *)mg->mg_ptr)) {
                len = -len;
            }
        }
        SHARED_CONTEXT;
        svp = hv_fetch((HV*) saggregate, key, len, 1);
    }
    CALLER_CONTEXT;
    Perl_sharedsv_associate(aTHX_ sv, *svp);
    sharedsv_scalar_store(aTHX_ sv, *svp);
    SvFLAGS(*svp) |= dualvar_flags;
    LEAVE_LOCK;
    return (0);
}
