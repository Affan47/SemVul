buf_put_pub_key(buffer* buf, sign_key *key, int type) {

	buffer *pubkeys;

	TRACE(("enter buf_put_pub_key"))
	pubkeys = buf_new(MAX_PUBKEY_SIZE);

#ifdef DROPBEAR_DSS
	if (type == DROPBEAR_SIGNKEY_DSS) {
		buf_put_dss_pub_key(pubkeys, key->dsskey);
	}
#endif
#ifdef DROPBEAR_RSA
	if (type == DROPBEAR_SIGNKEY_RSA) {
		buf_put_rsa_pub_key(pubkeys, key->rsakey);
	}
#endif
	if (pubkeys->len == 0) {
		dropbear_exit("bad key types in buf_put_pub_key");
	}

	buf_setpos(pubkeys, 0);
	buf_putstring(buf, buf_getptr(pubkeys, pubkeys->len),
			pubkeys->len);

	buf_free(pubkeys);
	TRACE(("leave buf_put_pub_key"))
}
