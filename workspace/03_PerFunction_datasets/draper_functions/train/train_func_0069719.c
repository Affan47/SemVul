ktest_equal_ldap_sequence_of_keys(ldap_seqof_key_data *ref,
                                  ldap_seqof_key_data *var)
{
    int p = TRUE;
    if (ref == var) return TRUE;
    else if (ref == NULL || var == NULL) return FALSE;
    p = p && scalar_equal(mkvno);
    p = p && scalar_equal(kvno);
    p = p && len_equal(n_key_data,key_data,equal_key_data_array);
    return p;
}
