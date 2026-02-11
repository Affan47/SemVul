ECDSA_do_sign_ex(const unsigned char *dgst, int dlen,
	const BIGNUM *kinv, const BIGNUM *rp, EC_KEY *eckey)
{
	ECDSA_DATA *ecdsa = ecdsa_check(eckey);
	if (ecdsa == NULL)
		return NULL;
	return ecdsa->meth->ecdsa_do_sign(dgst, dlen, kinv, rp, eckey);
}
