krb5_cc_retrieve_cred_seq (krb5_context context, krb5_ccache id,
                           krb5_flags whichfields, krb5_creds *mcreds,
                           krb5_creds *creds, int nktypes, krb5_enctype *ktypes)
{


    krb5_cc_cursor cursor;
    krb5_error_code kret;
    krb5_error_code nomatch_err = KRB5_CC_NOTFOUND;
    struct {
        krb5_creds creds;
        int pref;
    } fetched, best;
    int have_creds = 0;
    krb5_flags oflags = 0;
#define fetchcreds (fetched.creds)

    kret = krb5_cc_get_flags(context, id, &oflags);
    if (kret != KRB5_OK)
        return kret;
    if (oflags & KRB5_TC_OPENCLOSE)
        (void) krb5_cc_set_flags(context, id, oflags & ~KRB5_TC_OPENCLOSE);
    kret = krb5_cc_start_seq_get(context, id, &cursor);
    if (kret != KRB5_OK) {
        if (oflags & KRB5_TC_OPENCLOSE)
            krb5_cc_set_flags(context, id, oflags);
        return kret;
    }

    while (krb5_cc_next_cred(context, id, &cursor, &fetchcreds) == KRB5_OK) {
        if (krb5int_cc_creds_match_request(context, whichfields, mcreds, &fetchcreds))
        {
            if (ktypes) {
                fetched.pref = pref (fetchcreds.keyblock.enctype,
                                     nktypes, ktypes);
                if (fetched.pref < 0)
                    nomatch_err = KRB5_CC_NOT_KTYPE;
                else if (!have_creds || fetched.pref < best.pref) {
                    if (have_creds)
                        krb5_free_cred_contents (context, &best.creds);
                    else
                        have_creds = 1;
                    best = fetched;
                    continue;
                }
            } else {
                krb5_cc_end_seq_get(context, id, &cursor);
                *creds = fetchcreds;
                if (oflags & KRB5_TC_OPENCLOSE)
                    krb5_cc_set_flags(context, id, oflags);
                return KRB5_OK;
            }
        }


        krb5_free_cred_contents(context, &fetchcreds);
    }


    krb5_cc_end_seq_get(context, id, &cursor);
    if (oflags & KRB5_TC_OPENCLOSE)
        krb5_cc_set_flags(context, id, oflags);
    if (have_creds) {
        *creds = best.creds;
        return KRB5_OK;
    } else
        return nomatch_err;
}
