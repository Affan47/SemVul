rad_coa_recv(REQUEST *request)
{
	int rcode = RLM_MODULE_OK;
	int ack, nak;
	VALUE_PAIR *vp;


	switch (request->packet->code) {
	case PW_COA_REQUEST:
		ack = PW_COA_ACK;
		nak = PW_COA_NAK;
		break;

	case PW_DISCONNECT_REQUEST:
		ack = PW_DISCONNECT_ACK;
		nak = PW_DISCONNECT_NAK;
		break;

	default:
		return RLM_MODULE_FAIL;
	}

#ifdef WITH_PROXY
#define WAS_PROXIED (request->proxy)
#else
#define WAS_PROXIED (0)
#endif

	if (!WAS_PROXIED) {


		vp = pairfind(request->packet->vps, PW_SERVICE_TYPE, 0);
		if (request->packet->code == PW_COA_REQUEST) {
			if (vp && (vp->vp_integer == 17)) {
				vp = pairfind(request->packet->vps, PW_STATE, 0);
				if (!vp || (vp->length == 0)) {
					RDEBUG("ERROR: CoA-Request with Service-Type = Authorize-Only MUST contain a State attribute");
					request->reply->code = PW_COA_NAK;
					return RLM_MODULE_FAIL;
				}
			}
		} else if (vp) {


			RDEBUG("ERROR: Disconnect-Request MUST NOT contain a Service-Type attribute");
			request->reply->code = PW_DISCONNECT_NAK;
			return RLM_MODULE_FAIL;
		}

		rcode = module_recv_coa(0, request);
		switch (rcode) {
		case RLM_MODULE_FAIL:
		case RLM_MODULE_INVALID:
		case RLM_MODULE_REJECT:
		case RLM_MODULE_USERLOCK:
		default:
			request->reply->code = nak;
			break;

		case RLM_MODULE_HANDLED:
			return rcode;

		case RLM_MODULE_NOOP:
		case RLM_MODULE_NOTFOUND:
		case RLM_MODULE_OK:
		case RLM_MODULE_UPDATED:
			if (do_proxy(request)) return RLM_MODULE_OK;
			request->reply->code = ack;
			break;
		}
	} else if (request->proxy_reply) {


		request->reply->code = request->proxy_reply->code;
	}


	vp = paircopy2(request->packet->vps, PW_STATE, 0);
	if (vp) pairadd(&request->reply->vps, vp);


	if (request->reply->code) {
		rcode = module_send_coa(0, request);
		switch (rcode) {


		case RLM_MODULE_FAIL:
		case RLM_MODULE_INVALID:
		case RLM_MODULE_REJECT:
		case RLM_MODULE_USERLOCK:
		default:


			request->reply->code = nak;
			break;

		case RLM_MODULE_HANDLED:
			return rcode;

		case RLM_MODULE_NOOP:
		case RLM_MODULE_NOTFOUND:
		case RLM_MODULE_OK:
		case RLM_MODULE_UPDATED:


			if (request->reply->code == 0) {
				request->reply->code = ack;
			}
			break;
		}
	}

	return RLM_MODULE_OK;
}
