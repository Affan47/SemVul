ubsec_mod_exp_mont(BIGNUM *r, const BIGNUM *a, const BIGNUM *p,
		const BIGNUM *m, BN_CTX *ctx, BN_MONT_CTX *m_ctx)
        {
	int ret = 0;


	if (BN_num_bits(m) > max_key_len)
                {
		const RSA_METHOD *meth = RSA_PKCS1_SSLeay();
		ret = (*meth->bn_mod_exp)(r, a, p, m, ctx, m_ctx);
                }
        else
                {
		ret = ubsec_mod_exp(r, a, p, m, ctx);
                }

	return ret;
        }
