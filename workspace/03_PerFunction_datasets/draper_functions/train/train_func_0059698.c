buf_get_rsa_pub_key(buffer* buf, rsa_key *key) {

    int ret = DROPBEAR_FAILURE;
	TRACE(("enter buf_get_rsa_pub_key"))
	dropbear_assert(key != NULL);
	key->e = m_malloc(sizeof(mp_int));
	key->n = m_malloc(sizeof(mp_int));
	m_mp_init_multi(key->e, key->n, NULL);
	key->d = NULL;
	key->p = NULL;
	key->q = NULL;

	buf_incrpos(buf, 4+SSH_SIGNKEY_RSA_LEN);

	if (buf_getmpint(buf, key->e) == DROPBEAR_FAILURE
	 || buf_getmpint(buf, key->n) == DROPBEAR_FAILURE) {
		TRACE(("leave buf_get_rsa_pub_key: failure"))
	    goto out;
	}

	if (mp_count_bits(key->n) < MIN_RSA_KEYLEN) {
		dropbear_log(LOG_WARNING, "rsa key too short");
	    goto out;
	}

	TRACE(("leave buf_get_rsa_pub_key: success"))
    ret = DROPBEAR_SUCCESS;
out:
    if (ret == DROPBEAR_FAILURE) {
        m_free(key->e);
        m_free(key->n);
    }
	return ret;
}
