_gsskrb5_display_name
           (OM_uint32 * minor_status,
            gss_const_name_t input_name,
            gss_buffer_t output_name_buffer,
            gss_OID * output_name_type
           )
{
    krb5_context context;
    krb5_const_principal name = (krb5_const_principal)input_name;
    krb5_error_code kret;
    char *buf;
    size_t len;

    GSSAPI_KRB5_INIT (&context);

    kret = krb5_unparse_name_flags (context, name,
				    KRB5_PRINCIPAL_UNPARSE_DISPLAY, &buf);
    if (kret) {
	*minor_status = kret;
	return GSS_S_FAILURE;
    }
    len = strlen (buf);
    output_name_buffer->length = len;
    output_name_buffer->value  = malloc(len + 1);
    if (output_name_buffer->value == NULL) {
	free (buf);
	*minor_status = ENOMEM;
	return GSS_S_FAILURE;
    }
    memcpy (output_name_buffer->value, buf, len);
    ((char *)output_name_buffer->value)[len] = '\0';
    free (buf);
    if (output_name_type)
	*output_name_type = GSS_KRB5_NT_PRINCIPAL_NAME;
    *minor_status = 0;
    return GSS_S_COMPLETE;
}
