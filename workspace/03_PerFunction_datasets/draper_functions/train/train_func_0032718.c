ECDSA_sign_setup(EC_KEY *eckey, BN_CTX *ctx_in, BIGNUM **kinvp,
		BIGNUM **rp)
{
	ECDSA_DATA *ecdsa = ecdsa_check(eckey);
	if (ecdsa == NULL)
		return 0;
	return ecdsa->meth->ecdsa_sign_setup(eckey, ctx_in, kinvp, rp);
}
