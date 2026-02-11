ktest_equal_error(krb5_error *ref, krb5_error *var)
{
    int p = TRUE;
    if (ref == var) return TRUE;
    else if (ref == NULL || var == NULL) return FALSE;
    p = p && scalar_equal(ctime);
    p = p && scalar_equal(cusec);
    p = p && scalar_equal(susec);
    p = p && scalar_equal(stime);
    p = p && scalar_equal(error);
    p = p && ptr_equal(client,ktest_equal_principal_data);
    p = p && ptr_equal(server,ktest_equal_principal_data);
    p = p && struct_equal(text,ktest_equal_data);
    p = p && struct_equal(e_data,ktest_equal_data);
    return p;
}
