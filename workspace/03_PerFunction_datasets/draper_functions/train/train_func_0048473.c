kdc_tgs_req(krb5_context context,
	    krb5_kdc_configuration *config,
	    krb5_data *req_buffer,
	    krb5_data *reply,
	    const char *from,
	    struct sockaddr *addr,
	    int datagram_reply,
	    int *claim)
{
    krb5_error_code ret;
    KDC_REQ req;
    size_t len;

    ret = decode_TGS_REQ(req_buffer->data, req_buffer->length, &req, &len);
    if (ret)
	return ret;

    *claim = 1;

    ret = _kdc_tgs_rep(context, config, &req, reply,
		       from, addr, datagram_reply);
    free_TGS_REQ(&req);
    return ret;
}
