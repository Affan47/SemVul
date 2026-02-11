krb5_c_make_checksum(krb5_context context,
		     krb5_cksumtype cksumtype,
		     const krb5_keyblock *key,
		     krb5_keyusage usage,
		     const krb5_data *input,
		     krb5_checksum *cksum)
{
    krb5_error_code ret;
    krb5_crypto crypto;

    ret = krb5_crypto_init(context, key, 0, &crypto);
    if (ret)
	return ret;

    ret = krb5_create_checksum(context, crypto,  usage, cksumtype,
			       input->data, input->length, cksum);
    krb5_crypto_destroy(context, crypto);

    return ret ;
}
