sqlite_db_aggr_step_dispatcher(sqlite3_context *context,
                               int argc, sqlite3_value **value)
{
    dTHX;
    dSP;
    int i;
    aggrInfo *aggr;

    aggr = sqlite3_aggregate_context(context, sizeof (aggrInfo));
    if ( !aggr )
        return;

    ENTER;
    SAVETMPS;


    if ( !aggr->inited ) {
        sqlite_db_aggr_new_dispatcher(aTHX_ context, aggr);
    }

    if ( aggr->err || !aggr->aggr_inst )
        goto cleanup;

    PUSHMARK(SP);
    XPUSHs( sv_2mortal( newSVsv( aggr->aggr_inst ) ));
    for ( i=0; i < argc; i++ ) {
        SV *arg;
        int len = sqlite3_value_bytes(value[i]);
        int type = sqlite3_value_type(value[i]);

        switch(type) {
            case SQLITE_INTEGER:
                arg = sv_2mortal(newSViv(sqlite3_value_int(value[i])));
                break;
            case SQLITE_FLOAT:
                arg = sv_2mortal(newSVnv(sqlite3_value_double(value[i])));
                break;
            case SQLITE_TEXT:
                arg = sv_2mortal(newSVpvn((const char *)sqlite3_value_text(value[i]), len));
                break;
            case SQLITE_BLOB:
                arg = sv_2mortal(newSVpvn(sqlite3_value_blob(value[i]), len));
                break;
            default:
                arg = &PL_sv_undef;
        }

        XPUSHs(arg);
    }
    PUTBACK;

    call_method ("step", G_SCALAR|G_EVAL|G_DISCARD);


    if (SvTRUE(ERRSV) ) {
      aggr->err = newSVpvf("error during aggregator's step(): %s",
                            SvPV_nolen(ERRSV));
      POPs;
    }

 cleanup:
    FREETMPS;
    LEAVE;
}
