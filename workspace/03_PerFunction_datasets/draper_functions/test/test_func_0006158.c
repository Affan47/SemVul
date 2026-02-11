rsa_parse_pub_key(struct rsa_key *rsa_key, const void *key,
		      unsigned int key_len)
{
	int ret;

	free_mpis(rsa_key);
	ret = asn1_ber_decoder(&rsapubkey_decoder, rsa_key, key, key_len);
	if (ret < 0)
		goto error;

	return 0;
error:
	free_mpis(rsa_key);
	return ret;
}
