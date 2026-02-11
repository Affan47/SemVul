ktest_equal_enc_tkt_part(krb5_enc_tkt_part *ref, krb5_enc_tkt_part *var)
{
    int p = TRUE;
    if (ref == var) return TRUE;
    else if (ref == NULL || var == NULL) return FALSE;
    p = p && scalar_equal(flags);
    p = p && ptr_equal(session,ktest_equal_encryption_key);
    p = p && ptr_equal(client,ktest_equal_principal_data);
    p = p && struct_equal(transited,ktest_equal_transited);
    p = p && struct_equal(times,ktest_equal_ticket_times);
    p = p && ptr_equal(caddrs,ktest_equal_addresses);
    p = p && ptr_equal(authorization_data,ktest_equal_authorization_data);
    return p;
}
