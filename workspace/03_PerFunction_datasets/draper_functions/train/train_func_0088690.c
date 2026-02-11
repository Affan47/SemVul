der_put_octet_string (unsigned char *p, size_t len,
		      const heim_octet_string *data, size_t *size)
{
    if (len < data->length)
	return ASN1_OVERFLOW;
    p -= data->length;
    memcpy (p+1, data->data, data->length);
    *size = data->length;
    return 0;
}
