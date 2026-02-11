krb5_principal_get_comp_string(krb5_context context,
			       krb5_const_principal principal,
			       unsigned int component)
{
    if(component >= princ_num_comp(principal))
       return NULL;
    return princ_ncomp(principal, component);
}
