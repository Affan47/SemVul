_gssapi_get_mic_arcfour(OM_uint32 * minor_status,
			const gsskrb5_ctx context_handle,
			krb5_context context,
			gss_qop_t qop_req,
			const gss_buffer_t message_buffer,
			gss_buffer_t message_token,
			krb5_keyblock *key)
{
    krb5_error_code ret;
    int32_t seq_number;
    size_t len, total_len;
    u_char k6_data[16], *p0, *p;
    EVP_CIPHER_CTX rc4_key;

    _gsskrb5_encap_length (22, &len, &total_len, GSS_KRB5_MECHANISM);

    message_token->length = total_len;
    message_token->value  = malloc (total_len);
    if (message_token->value == NULL) {
	*minor_status = ENOMEM;
	return GSS_S_FAILURE;
    }

    p0 = _gssapi_make_mech_header(message_token->value,
				  len,
				  GSS_KRB5_MECHANISM);
    p = p0;

    *p++ = 0x01;
    *p++ = 0x01;
    *p++ = 0x11;
    *p++ = 0x00;
    *p++ = 0xff;
    *p++ = 0xff;
    *p++ = 0xff;
    *p++ = 0xff;

    p = NULL;

    ret = arcfour_mic_cksum(context,
			    key, KRB5_KU_USAGE_SIGN,
			    p0 + 16, 8,
			    p0, 8,
			    message_buffer->value, message_buffer->length,
			    NULL, 0);
    if (ret) {
	_gsskrb5_release_buffer(minor_status, message_token);
	*minor_status = ret;
	return GSS_S_FAILURE;
    }

    ret = arcfour_mic_key(context, key,
			  p0 + 16, 8,
			  k6_data, sizeof(k6_data));
    if (ret) {
	_gsskrb5_release_buffer(minor_status, message_token);
	*minor_status = ret;
	return GSS_S_FAILURE;
    }

    HEIMDAL_MUTEX_lock(&context_handle->ctx_id_mutex);
    krb5_auth_con_getlocalseqnumber (context,
				     context_handle->auth_context,
				     &seq_number);
    p = p0 + 8;
    _gsskrb5_encode_be_om_uint32(seq_number, p);

    krb5_auth_con_setlocalseqnumber (context,
				     context_handle->auth_context,
				     ++seq_number);
    HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);

    memset (p + 4, (context_handle->more_flags & LOCAL) ? 0 : 0xff, 4);

    EVP_CIPHER_CTX_init(&rc4_key);
    EVP_CipherInit_ex(&rc4_key, EVP_rc4(), NULL, k6_data, NULL, 1);
    EVP_Cipher(&rc4_key, p, p, 8);
    EVP_CIPHER_CTX_cleanup(&rc4_key);

    memset(k6_data, 0, sizeof(k6_data));

    *minor_status = 0;
    return GSS_S_COMPLETE;
}
