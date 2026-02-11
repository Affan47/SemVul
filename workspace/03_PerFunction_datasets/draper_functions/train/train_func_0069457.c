decrypt_buf(u8 *buf, int size, u8 *key, int key_type)
{
	int i, retv;
	u8 tmp[16];

	memcpy(tmp, buf + size + 0x14 - 16, 16);

	retv = kirk7(buf, size, key_type);

	if (retv)
		return retv;

	for (i = 0; i < 16; i++) {
		buf[i] ^= key[i];
	}

	memcpy(key, tmp, 16);

	return 0;
}
