krb5_mcc_next_cred(krb5_context context, krb5_ccache id,
                   krb5_cc_cursor *cursor, krb5_creds *creds)
{
    krb5_mcc_cursor mcursor;
    krb5_error_code retval;


    mcursor = (krb5_mcc_cursor) *cursor;
    if (mcursor == NULL)
        return KRB5_CC_END;
    memset(creds, 0, sizeof(krb5_creds));
    if (mcursor->creds) {
        retval = k5_copy_creds_contents(context, mcursor->creds, creds);
        if (retval)
            return retval;
    }
    *cursor = (krb5_cc_cursor)mcursor->next;
    return KRB5_OK;
}
