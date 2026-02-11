krb5_verify_checksum(krb5_context context,
		     krb5_crypto crypto,
		     krb5_key_usage usage,
		     void *data,
		     size_t len,
		     Checksum *cksum)
{
    struct _krb5_checksum_type *ct;
    unsigned keyusage;

    ct = _krb5_find_checksum(cksum->cksumtype);
    if(ct == NULL) {
	krb5_set_error_message (context, KRB5_PROG_SUMTYPE_NOSUPP,
				N_("checksum type %d not supported", ""),
				cksum->cksumtype);
	return KRB5_PROG_SUMTYPE_NOSUPP;
    }

    if (arcfour_checksum_p(ct, crypto)) {
	keyusage = usage;
	_krb5_usage2arcfour(context, &keyusage);
    } else
	keyusage = CHECKSUM_USAGE(usage);

    return verify_checksum(context, crypto, keyusage,
			   data, len, cksum);
}
