seqiv_create(struct crypto_template *tmpl, struct rtattr **tb)
{
	struct crypto_attr_type *algt;
	int err;

	algt = crypto_get_attr_type(tb);
	if (IS_ERR(algt))
		return PTR_ERR(algt);

	if ((algt->type ^ CRYPTO_ALG_TYPE_AEAD) & CRYPTO_ALG_TYPE_MASK)
		err = seqiv_ablkcipher_create(tmpl, tb);
	else
		err = seqiv_aead_create(tmpl, tb);

	return err;
}
