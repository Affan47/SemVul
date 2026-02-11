pv_get_authattr(struct sip_msg *msg, pv_param_t *param,
		pv_value_t *res)
{
	struct hdr_field *hdr;

    if(msg==NULL)
		return -1;

	if ((msg->REQ_METHOD == METHOD_ACK) ||
			(msg->REQ_METHOD == METHOD_CANCEL)) {
		LM_DBG("no [Proxy-]Authorization header\n");
		return pv_get_null(msg, param, res);
	}

	if ((parse_headers(msg, HDR_PROXYAUTH_F|HDR_AUTHORIZATION_F, 0)==-1)
			|| (msg->proxy_auth==0 && msg->authorization==0))
	{
		LM_DBG("no [Proxy-]Authorization header\n");
		return pv_get_null(msg, param, res);
	}

	hdr = (msg->proxy_auth==0)?msg->authorization:msg->proxy_auth;

	if(parse_credentials(hdr)!=0) {
	        LM_ERR("failed to parse credentials\n");
		return pv_get_null(msg, param, res);
	}
	switch(param->pvn.u.isname.name.n)
	{
		case 6:
			return pv_get_strval(msg, param, res,
					&((auth_body_t*)(hdr->parsed))->digest.response);
		case 5:
			return pv_get_strval(msg, param, res,
					&((auth_body_t*)(hdr->parsed))->digest.nonce);
		case 4:
			return pv_get_strval(msg, param, res,
					&((auth_body_t*)(hdr->parsed))->digest.username.domain);
		case 3:
			if(((auth_body_t*)(hdr->parsed))->digest.uri.len==0)
				return pv_get_null(msg, param, res);
			return pv_get_strval(msg, param, res,
					&((auth_body_t*)(hdr->parsed))->digest.uri);
		break;
		case 2:
			return pv_get_strval(msg, param, res,
					&((auth_body_t*)(hdr->parsed))->digest.realm);
		break;
		case 1:
			return pv_get_strval(msg, param, res,
					&((auth_body_t*)(hdr->parsed))->digest.username.user);
		break;
		default:
			return pv_get_strval(msg, param, res,
					&((auth_body_t*)(hdr->parsed))->digest.username.whole);
	}
}
