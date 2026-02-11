hmacsha224_tofile(const dst_key_t *key, const char *directory) {
	int cnt = 0;
	dst_hmacsha224_key_t *hkey;
	dst_private_t priv;
	int bytes = (key->key_size + 7) / 8;
	unsigned char buf[2];

	if (key->keydata.hmacsha224 == NULL)
		return (DST_R_NULLKEY);

	if (key->external)
		return (DST_R_EXTERNALKEY);

	hkey = key->keydata.hmacsha224;

	priv.elements[cnt].tag = TAG_HMACSHA224_KEY;
	priv.elements[cnt].length = bytes;
	priv.elements[cnt++].data = hkey->key;

	buf[0] = (key->key_bits >> 8) & 0xffU;
	buf[1] = key->key_bits & 0xffU;
	priv.elements[cnt].tag = TAG_HMACSHA224_BITS;
	priv.elements[cnt].data = buf;
	priv.elements[cnt++].length = 2;

	priv.nelements = cnt;
	return (dst__privstruct_writefile(key, &priv, directory));
}
