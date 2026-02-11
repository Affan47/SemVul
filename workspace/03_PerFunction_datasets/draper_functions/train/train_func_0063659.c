unparse_name(krb5_context context,
	     krb5_const_principal principal,
	     char **name,
	     int flags)
{
    size_t len = 0, plen;
    size_t i;
    krb5_error_code ret;

    if (princ_realm(principal)) {
	plen = strlen(princ_realm(principal));

	if(strcspn(princ_realm(principal), quotable_chars) == plen)
	    len += plen;
	else
	    len += 2*plen;
	len++;
    }
    for(i = 0; i < princ_num_comp(principal); i++){
	plen = strlen(princ_ncomp(principal, i));
	if(strcspn(princ_ncomp(principal, i), quotable_chars) == plen)
	    len += plen;
	else
	    len += 2*plen;
	len++;
    }
    len++;
    *name = malloc(len);
    if(*name == NULL)
	return krb5_enomem(context);
    ret = unparse_name_fixed(context, principal, *name, len, flags);
    if(ret) {
	free(*name);
	*name = NULL;
    }
    return ret;
}
