find_authdata_1(krb5_context context, krb5_authdata *const *in_authdat,
                krb5_authdatatype ad_type, struct find_authdata_context *fctx,
                int from_ap_req)
{
    int i = 0;
    krb5_error_code retval = 0;

    for (i = 0; in_authdat[i] && retval == 0; i++) {
        krb5_authdata *ad = in_authdat[i];
        krb5_authdata **decoded_container;

        switch (ad->ad_type) {
        case KRB5_AUTHDATA_IF_RELEVANT:
            if (retval == 0)
                retval = krb5_decode_authdata_container(context,
                                                        ad->ad_type,
                                                        ad,
                                                        &decoded_container);
            if (retval == 0) {
                retval = find_authdata_1(context,
                                         decoded_container,
                                         ad_type,
                                         fctx,
                                         from_ap_req);
                krb5_free_authdata(context, decoded_container);
            }
            break;
        case KRB5_AUTHDATA_SIGNTICKET:
        case KRB5_AUTHDATA_KDC_ISSUED:
        case KRB5_AUTHDATA_WIN2K_PAC:
            if (from_ap_req)
                continue;
        default:
            if (ad->ad_type == ad_type && retval == 0)
                retval = grow_find_authdata(context, fctx, ad);
            break;
        }
    }

    return retval;
}
