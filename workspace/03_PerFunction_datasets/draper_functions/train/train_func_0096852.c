_gssapi_encapsulate(
    OM_uint32 *minor_status,
    const krb5_data *in_data,
    gss_buffer_t output_token,
    const gss_OID mech
)
{
    size_t len, outer_len;
    void *p;

    _gssapi_encap_length (in_data->length, &len, &outer_len, mech);

    output_token->length = outer_len;
    output_token->value  = malloc (outer_len);
    if (output_token->value == NULL) {
	*minor_status = ENOMEM;
	return GSS_S_FAILURE;
    }

    p = _gssapi_make_mech_header (output_token->value, len, mech);
    memcpy (p, in_data->data, in_data->length);
    return GSS_S_COMPLETE;
}
