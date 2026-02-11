ktest_equal_as_rep(krb5_kdc_rep *ref, krb5_kdc_rep *var)
{
    int p = TRUE;
    if (ref == var) return TRUE;
    else if (ref == NULL || var == NULL) return FALSE;
    p = p && scalar_equal(msg_type);
    p = p && ptr_equal(padata,ktest_equal_sequence_of_pa_data);
    p = p && ptr_equal(client,ktest_equal_principal_data);
    p = p && ptr_equal(ticket,ktest_equal_ticket);
    p = p && struct_equal(enc_part,ktest_equal_enc_data);
    p = p && ptr_equal(enc_part2,ktest_equal_enc_kdc_rep_part);
    return p;
}
