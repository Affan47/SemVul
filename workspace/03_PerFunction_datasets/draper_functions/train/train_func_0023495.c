krb5_c_get_checksum(krb5_context context, const krb5_checksum *cksum,
		    krb5_cksumtype *type, krb5_data **data)
{
    krb5_error_code ret;

    if (type)
	*type = cksum->cksumtype;
    if (data) {
	*data = malloc(sizeof(**data));
	if (*data == NULL)
	    return krb5_enomem(context);

	ret = der_copy_octet_string(&cksum->checksum, *data);
	if (ret) {
	    free(*data);
	    *data = NULL;
	    return ret;
	}
    }
    return 0;
}
