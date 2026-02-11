eap_post_proxy(void *inst, REQUEST *request)
{
	size_t		i;
	size_t		len;
	VALUE_PAIR	*vp;
	EAP_HANDLER	*handler;


	handler = request_data_get(request, inst, REQUEST_DATA_EAP_HANDLER);
	if (handler != NULL) {
		int		rcode;
		eap_tunnel_data_t *data;


		data = (eap_tunnel_data_t *) request_data_get(request,
							      request->proxy,
							      REQUEST_DATA_EAP_TUNNEL_CALLBACK);
		if (!data) {
			radlog_request(L_ERR, 0, request, "Failed to retrieve callback for tunneled session!");
			eap_handler_free(inst, handler);
			return RLM_MODULE_FAIL;
		}


		RDEBUG2("Doing post-proxy callback");
		rcode = data->callback(handler, data->tls_session);
		free(data);
		if (rcode == 0) {
			RDEBUG2("Failed in post-proxy callback");
			eap_fail(handler);
			eap_handler_free(inst, handler);
			return RLM_MODULE_REJECT;
		}


		eap_compose(handler);


		if ((handler->eap_ds->request->code == PW_EAP_REQUEST) &&
		    (handler->eap_ds->request->type.type >= PW_EAP_MD5)) {
			if (!eaplist_add(inst, handler)) {
				eap_fail(handler);
				eap_handler_free(inst, handler);
				return RLM_MODULE_FAIL;
			}

		} else {
			RDEBUG2("Freeing handler");

			eap_handler_free(inst, handler);
		}


		if ((request->reply->code == PW_AUTHENTICATION_ACK) &&
		    request->username) {


			vp = pairfind(request->reply->vps, PW_USER_NAME);
			if (!vp) {
				vp = pairmake("User-Name", request->username->vp_strvalue,
					      T_OP_EQ);
				rad_assert(vp != NULL);
				pairadd(&(request->reply->vps), vp);
			}
		}

		return RLM_MODULE_OK;
	} else {
		RDEBUG2("No pre-existing handler found");
	}


	vp = request->proxy_reply->vps;
	for (;;) {


		vp = pairfind(vp, (9 << 16)  | 1);
		if (!vp) {
			return RLM_MODULE_NOOP;
		}


		if (strncasecmp(vp->vp_strvalue, "leap:session-key=", 17) == 0) {
			break;
		}


		vp = vp->next;
	}


	if (vp->length != 17 + 34) {
		RDEBUG2("Cisco-AVPair with leap:session-key has incorrect length %d: Expected %d",
		       vp->length, 17 + 34);
		return RLM_MODULE_NOOP;
	}


	i = 34;
	len = rad_tunnel_pwdecode(vp->vp_octets + 17, &i,
				  request->home_server->secret,
				  request->proxy->vector);


	rad_tunnel_pwencode(vp->vp_strvalue + 17, &len,
			    request->client->secret,
			    request->packet->vector);

	return RLM_MODULE_UPDATED;
}
