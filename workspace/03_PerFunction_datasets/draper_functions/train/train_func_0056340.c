dh_bn_mod_exp(const DH *dh, BIGNUM *r,
			const BIGNUM *a, const BIGNUM *p,
			const BIGNUM *m, BN_CTX *ctx,
			BN_MONT_CTX *m_ctx)
	{


	if (a->top == 1 && ((dh->flags & DH_FLAG_NO_EXP_CONSTTIME) != 0))
		{
		BN_ULONG A = a->d[0];
		return BN_mod_exp_mont_word(r,A,p,m,ctx,m_ctx);
		}
	else
		return BN_mod_exp_mont(r,a,p,m,ctx,m_ctx);
	}
