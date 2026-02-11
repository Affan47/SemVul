_gssapi_verify_mic_arcfour(OM_uint32 * minor_status,
			   const gsskrb5_ctx context_handle,
			   krb5_context context,
			   const gss_buffer_t message_buffer,
			   const gss_buffer_t token_buffer,
			   gss_qop_t * qop_state,
			   krb5_keyblock *key,
			   const char *type)
{
    krb5_error_code ret;
    uint32_t seq_number;
    OM_uint32 omret;
    u_char SND_SEQ[8], cksum_data[8], *p;
    char k6_data[16];
    int cmp;

    if (qop_state)
	*qop_state = 0;

    p = token_buffer->value;
    omret = _gsskrb5_verify_header (&p,
				       token_buffer->length,
				       type,
				       GSS_KRB5_MECHANISM);
    if (omret)
	return omret;

    if (memcmp(p, "\x11\x00", 2) != 0)
	return GSS_S_BAD_SIG;
    p += 2;
    if (memcmp (p, "\xff\xff\xff\xff", 4) != 0)
	return GSS_S_BAD_MIC;
    p += 4;

    ret = arcfour_mic_cksum(context,
			    key, KRB5_KU_USAGE_SIGN,
			    cksum_data, sizeof(cksum_data),
			    p - 8, 8,
			    message_buffer->value, message_buffer->length,
			    NULL, 0);
    if (ret) {
	*minor_status = ret;
	return GSS_S_FAILURE;
    }

    ret = arcfour_mic_key(context, key,
			  cksum_data, sizeof(cksum_data),
			  k6_data, sizeof(k6_data));
    if (ret) {
	*minor_status = ret;
	return GSS_S_FAILURE;
    }

    cmp = ct_memcmp(cksum_data, p + 8, 8);
    if (cmp) {
	*minor_status = 0;
	return GSS_S_BAD_MIC;
    }

    {
	EVP_CIPHER_CTX rc4_key;

	EVP_CIPHER_CTX_init(&rc4_key);
	EVP_CipherInit_ex(&rc4_key, EVP_rc4(), NULL, (void *)k6_data, NULL, 0);
	EVP_Cipher(&rc4_key, SND_SEQ, p, 8);
	EVP_CIPHER_CTX_cleanup(&rc4_key);

	memset(k6_data, 0, sizeof(k6_data));
    }

    _gsskrb5_decode_be_om_uint32(SND_SEQ, &seq_number);

    if (context_handle->more_flags & LOCAL)
	cmp = memcmp(&SND_SEQ[4], "\xff\xff\xff\xff", 4);
    else
	cmp = memcmp(&SND_SEQ[4], "\x00\x00\x00\x00", 4);

    memset(SND_SEQ, 0, sizeof(SND_SEQ));
    if (cmp != 0) {
	*minor_status = 0;
	return GSS_S_BAD_MIC;
    }

    HEIMDAL_MUTEX_lock(&context_handle->ctx_id_mutex);
    omret = _gssapi_msg_order_check(context_handle->order, seq_number);
    HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);
    if (omret)
	return omret;

    *minor_status = 0;
    return GSS_S_COMPLETE;
}
