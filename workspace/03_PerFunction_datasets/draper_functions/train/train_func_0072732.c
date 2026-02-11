dbih_getcom2(pTHX_ SV *hrv, MAGIC **mgp)
{
    MAGIC *mg;
    SV *sv;


    if (SvROK(hrv))
        sv = SvRV(hrv);
    else {
        dMY_CXT;
        if (hrv == DBI_LAST_HANDLE)
            sv = DBI_LAST_HANDLE;
        else if (sv_derived_from(hrv, "DBI::common")) {

            return 0;
        }
        else {
            sv_dump(hrv);
            croak("Invalid DBI handle %s", neatsvpv(hrv,0));
            sv = &PL_sv_undef;
        }
    }


    if (SvRMAGICAL(sv) && (mg=SvMAGIC(sv))->mg_type == DBI_MAGIC) {

    }
    else {

        hrv = dbih_inner(aTHX_ hrv, "dbih_getcom");
        mg  = mg_find(SvRV(hrv), DBI_MAGIC);
    }
    if (mgp)
        *mgp = mg;

    if (!mg)
        return (imp_xxh_t *) 0;

    return (imp_xxh_t *) mg->mg_ptr;
}
