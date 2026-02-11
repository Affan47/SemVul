code_NegTokenArg(OM_uint32 *minor_status,
		 const NegTokenTarg *targ,
		 unsigned char **outbuf,
		 size_t *outbuf_size)
{
    OM_uint32 ret;
    u_char *buf;
    size_t buf_size, buf_len;

    buf_size = 1024;
    buf = malloc(buf_size);
    if (buf == NULL) {
	*minor_status = ENOMEM;
	return GSS_S_FAILURE;
    }

    do {
	ret = encode_NegTokenTarg(buf + buf_size -1,
				  buf_size,
				  targ, &buf_len);
	if (ret == 0) {
	    size_t tmp;

	    ret = der_put_length_and_tag(buf + buf_size - buf_len - 1,
					 buf_size - buf_len,
					 buf_len,
					 KERB_CTXT,
					 CONS,
					 1,
					 &tmp);
	    if (ret == 0)
		buf_len += tmp;
	}
	if (ret) {
	    if (ret == ASN1_OVERFLOW) {
		u_char *tmp;

		buf_size *= 2;
		tmp = realloc (buf, buf_size);
		if (tmp == NULL) {
		    *minor_status = ENOMEM;
		    free(buf);
		    return GSS_S_FAILURE;
		}
		buf = tmp;
	    } else {
		*minor_status = ret;
		free(buf);
		return GSS_S_FAILURE;
	    }
	}
    } while (ret == ASN1_OVERFLOW);

    *outbuf = malloc(buf_len);
    if (*outbuf == NULL) {
       *minor_status = ENOMEM;
       free(buf);
       return GSS_S_FAILURE;
    }

    memcpy(*outbuf, buf + buf_size - buf_len, buf_len);
    *outbuf_size = buf_len;

    free(buf);

    return GSS_S_COMPLETE;
}
