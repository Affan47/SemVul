ldns_resolver_set_tsig_keydata(ldns_resolver *r, char *tsig_keydata)
{
	LDNS_FREE(r->_tsig_keydata);
	r->_tsig_keydata = strdup(tsig_keydata);
}
