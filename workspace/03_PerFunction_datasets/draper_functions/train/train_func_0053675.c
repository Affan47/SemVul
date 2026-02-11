buf_get_dss_priv_key(buffer* buf, dss_key *key) {

	int ret = DROPBEAR_FAILURE;

	dropbear_assert(key != NULL);

	ret = buf_get_dss_pub_key(buf, key);
	if (ret == DROPBEAR_FAILURE) {
		return DROPBEAR_FAILURE;
	}

	key->x = m_malloc(sizeof(mp_int));
	m_mp_init(key->x);
	ret = buf_getmpint(buf, key->x);
	if (ret == DROPBEAR_FAILURE) {
		m_free(key->x);
	}

	return ret;
}
