stun_attr_add_integrity_by_user_str(u08bits *buf, size_t *len, u08bits *uname, u08bits *realm, u08bits *upwd, u08bits *nonce, SHATYPE shatype)
{
	hmackey_t key;

	if(stun_produce_integrity_key_str(uname, realm, upwd, key, shatype)<0)
		return -1;

	return stun_attr_add_integrity_by_key_str(buf, len, uname, realm, key, nonce, shatype);
}
