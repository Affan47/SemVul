ia_make_key(struct data_string *key, u_int32_t iaid,
	    const char *duid, unsigned int duid_len,
	    const char *file, int line) {

	memset(key, 0, sizeof(*key));
	key->len = duid_len + sizeof(iaid);
	if (!buffer_allocate(&(key->buffer), key->len, file, line)) {
		return ISC_R_NOMEMORY;
	}
	key->data = key->buffer->data;
	memcpy((char *)key->data, &iaid, sizeof(iaid));
	memcpy((char *)key->data + sizeof(iaid), duid, duid_len);

	return ISC_R_SUCCESS;
}
