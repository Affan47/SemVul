krb5_address_search(krb5_context context,
		    const krb5_address *addr,
		    const krb5_addresses *addrlist)
{
    size_t i;

    for (i = 0; i < addrlist->len; ++i)
	if (krb5_address_compare (context, addr, &addrlist->val[i]))
	    return TRUE;
    return FALSE;
}
