openssldh_isprivate(const dst_key_t *key) {
	DH *dh = key->keydata.dh;
	return (ISC_TF(dh != NULL && dh->priv_key != NULL));
}
