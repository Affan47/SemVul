get_cred_kdc_address(krb5_context context,
		     krb5_ccache id,
		     krb5_kdc_flags flags,
		     krb5_addresses *addrs,
		     krb5_creds *in_creds,
		     krb5_creds *krbtgt,
		     krb5_principal impersonate_principal,
		     Ticket *second_ticket,
		     krb5_creds *out_creds)
{
    krb5_error_code ret;
    krb5_addresses addresses = { 0, NULL };


    if (addrs == NULL && krbtgt->addresses.len != 0) {
	krb5_boolean noaddr;

	krb5_appdefault_boolean(context, NULL, krbtgt->server->realm,
				"no-addresses", FALSE, &noaddr);

	if (!noaddr) {
	    krb5_get_all_client_addrs(context, &addresses);

	    addrs = &addresses;
	    if(addresses.len == 0)
		addrs = NULL;
	}
    }
    ret = get_cred_kdc(context, id, flags, addrs, in_creds,
		       krbtgt, impersonate_principal,
		       second_ticket, out_creds);
    krb5_free_addresses(context, &addresses);
    return ret;
}
