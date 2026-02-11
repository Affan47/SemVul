krb5_c_decrypt(krb5_context context,
	       const krb5_keyblock key,
	       krb5_keyusage usage,
	       const krb5_data *ivec,
	       krb5_enc_data *input,
	       krb5_data *output)
{
    krb5_error_code ret;
    krb5_crypto crypto;

    ret = krb5_crypto_init(context, &key, input->enctype, &crypto);
    if (ret)
	return ret;

    if (ivec) {
	size_t blocksize;

	ret = krb5_crypto_getblocksize(context, crypto, &blocksize);
	if (ret) {
	krb5_crypto_destroy(context, crypto);
	return ret;
	}

	if (blocksize > ivec->length) {
	    krb5_crypto_destroy(context, crypto);
	    return KRB5_BAD_MSIZE;
	}
    }

    ret = krb5_decrypt_ivec(context, crypto, usage,
			    input->ciphertext.data, input->ciphertext.length,
			    output,
			    ivec ? ivec->data : NULL);

    krb5_crypto_destroy(context, crypto);

    return ret ;
}
