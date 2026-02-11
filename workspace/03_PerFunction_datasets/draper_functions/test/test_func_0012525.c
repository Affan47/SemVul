psk_client_cb(SSL *ssl, const char *hint, char *identity,
	unsigned int max_identity_len, unsigned char *psk,
	unsigned int max_psk_len)
	{
	unsigned int psk_len = 0;
	int ret;
        BIGNUM *bn=NULL;

	if (c_debug)
		BIO_printf(bio_c_out, "psk_client_cb\n");
	if (!hint)
                {

		if (c_debug)
			BIO_printf(bio_c_out,"NULL received PSK identity hint, continuing anyway\n");
                }
        else if (c_debug)
		BIO_printf(bio_c_out, "Received PSK identity hint '%s'\n", hint);


	ret = BIO_snprintf(identity, max_identity_len, "%s", psk_identity);
	if (ret < 0 || (unsigned int)ret > max_identity_len)
		goto out_err;
	if (c_debug)
		BIO_printf(bio_c_out, "created identity '%s' len=%d\n", identity, ret);
        ret=BN_hex2bn(&bn, psk_key);
        if (!ret)
                {
                BIO_printf(bio_err,"Could not convert PSK key '%s' to BIGNUM\n", psk_key);
                if (bn)
                        BN_free(bn);
                return 0;
                }

        if ((unsigned int)BN_num_bytes(bn) > max_psk_len)
                {
                BIO_printf(bio_err,"psk buffer of callback is too small (%d) for key (%d)\n",
                        max_psk_len, BN_num_bytes(bn));
                BN_free(bn);
                return 0;
                }

        psk_len=BN_bn2bin(bn, psk);
        BN_free(bn);
        if (psk_len == 0)
                goto out_err;

	if (c_debug)
		BIO_printf(bio_c_out, "created PSK len=%d\n", psk_len);

        return psk_len;
 out_err:
	if (c_debug)
		BIO_printf(bio_err, "Error in PSK client callback\n");
        return 0;
	}
