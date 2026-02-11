BN_gcd(BIGNUM *r, const BIGNUM *in_a, const BIGNUM *in_b, BN_CTX *ctx)
	{
	BIGNUM *a,*b,*t;
	int ret=0;

	bn_check_top(in_a);
	bn_check_top(in_b);

	BN_CTX_start(ctx);
	a = BN_CTX_get(ctx);
	b = BN_CTX_get(ctx);
	if (a == NULL || b == NULL) goto err;

	if (BN_copy(a,in_a) == NULL) goto err;
	if (BN_copy(b,in_b) == NULL) goto err;
	a->neg = 0;
	b->neg = 0;

	if (BN_cmp(a,b) < 0) { t=a; a=b; b=t; }
	t=euclid(a,b);
	if (t == NULL) goto err;

	if (BN_copy(r,t) == NULL) goto err;
	ret=1;
err:
	BN_CTX_end(ctx);
	bn_check_top(r);
	return(ret);
	}
