gss_encapsulate_token(gss_const_buffer_t input_token,
		      gss_const_OID oid,
		      gss_buffer_t output_token)
{
    GSSAPIContextToken ct;
    int ret;
    size_t size;

    ret = der_get_oid (oid->elements, oid->length, &ct.thisMech, &size);
    if (ret) {
	_mg_buffer_zero(output_token);
	return GSS_S_FAILURE;
    }

    ct.innerContextToken.data = input_token->value;
    ct.innerContextToken.length = input_token->length;

    ASN1_MALLOC_ENCODE(GSSAPIContextToken,
		       output_token->value, output_token->length,
		       &ct, &size, ret);
    der_free_oid(&ct.thisMech);
    if (ret) {
	_mg_buffer_zero(output_token);
	return GSS_S_FAILURE;
    }
    if (output_token->length != size)
	abort();

    return GSS_S_COMPLETE;
}
