ktest_equal_kdc_req_body(krb5_kdc_req *ref, krb5_kdc_req *var)
{
    int p = TRUE;
    if (ref == var) return TRUE;
    else if (ref == NULL || var == NULL) return FALSE;
    p = p && scalar_equal(kdc_options);
    p = p && ptr_equal(client,ktest_equal_principal_data);
    p = p && ptr_equal(server,ktest_equal_principal_data);
    p = p && scalar_equal(from);
    p = p && scalar_equal(till);
    p = p && scalar_equal(rtime);
    p = p && scalar_equal(nonce);
    p = p && len_equal(nktypes,ktype,ktest_equal_array_of_enctype);
    p = p && ptr_equal(addresses,ktest_equal_addresses);
    p = p && struct_equal(authorization_data,ktest_equal_enc_data);


    return p;
}
