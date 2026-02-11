encrypt_internal_derived(krb5_context context,
			 krb5_crypto crypto,
			 unsigned usage,
			 const void *data,
			 size_t len,
			 krb5_data *result,
			 void *ivec)
{
    size_t sz, block_sz, checksum_sz, total_sz;
    Checksum cksum;
    unsigned char *p, *q;
    krb5_error_code ret;
    struct _krb5_key_data *dkey;
    const struct _krb5_encryption_type *et = crypto->et;

    checksum_sz = CHECKSUMSIZE(et->keyed_checksum);

    sz = et->confoundersize + len;
    block_sz = (sz + et->padsize - 1) &~ (et->padsize - 1);
    total_sz = block_sz + checksum_sz;
    p = calloc(1, total_sz);
    if (p == NULL)
	return krb5_enomem(context);

    q = p;
    krb5_generate_random_block(q, et->confoundersize);
    q += et->confoundersize;
    memcpy(q, data, len);

    ret = create_checksum(context,
			  et->keyed_checksum,
			  crypto,
			  INTEGRITY_USAGE(usage),
			  p,
			  block_sz,
			  &cksum);
    if(ret == 0 && cksum.checksum.length != checksum_sz) {
	free_Checksum (&cksum);
	krb5_clear_error_message (context);
	ret = KRB5_CRYPTO_INTERNAL;
    }
    if(ret)
	goto fail;
    memcpy(p + block_sz, cksum.checksum.data, cksum.checksum.length);
    free_Checksum (&cksum);
    ret = _get_derived_key(context, crypto, ENCRYPTION_USAGE(usage), &dkey);
    if(ret)
	goto fail;
    ret = _key_schedule(context, dkey);
    if(ret)
	goto fail;
    ret = (*et->encrypt)(context, dkey, p, block_sz, 1, usage, ivec);
    if (ret)
	goto fail;
    result->data = p;
    result->length = total_sz;
    return 0;
 fail:
    memset(p, 0, total_sz);
    free(p);
    return ret;
}
