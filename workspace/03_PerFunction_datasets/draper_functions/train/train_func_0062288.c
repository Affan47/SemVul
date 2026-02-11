eap_basic_compose(RADIUS_PACKET *packet, EAP_PACKET *reply)
{
	VALUE_PAIR *vp;
	eap_packet_t *eap_packet;
	int rcode;

	if (eap_wireformat(reply) == EAP_INVALID) {
		return RLM_MODULE_INVALID;
	}
	eap_packet = (eap_packet_t *)reply->packet;

	pairdelete(&(packet->vps), PW_EAP_MESSAGE, 0);

	vp = eap_packet2vp(eap_packet);
	if (!vp) return RLM_MODULE_INVALID;
	pairadd(&(packet->vps), vp);


	vp = pairfind(packet->vps, PW_MESSAGE_AUTHENTICATOR, 0);
	if (!vp) {
		vp = paircreate(PW_MESSAGE_AUTHENTICATOR, 0, PW_TYPE_OCTETS);
		memset(vp->vp_strvalue, 0, AUTH_VECTOR_LEN);
		vp->length = AUTH_VECTOR_LEN;
		pairadd(&(packet->vps), vp);
	}


	rcode = RLM_MODULE_OK;
	if (!packet->code) switch(reply->code) {
	case PW_EAP_RESPONSE:
	case PW_EAP_SUCCESS:
		packet->code = PW_AUTHENTICATION_ACK;
		rcode = RLM_MODULE_HANDLED;
		break;
	case PW_EAP_FAILURE:
		packet->code = PW_AUTHENTICATION_REJECT;
		rcode = RLM_MODULE_REJECT;
		break;
	case PW_EAP_REQUEST:
		packet->code = PW_ACCESS_CHALLENGE;
		rcode = RLM_MODULE_HANDLED;
		break;
	default:

		radlog(L_ERR, "rlm_eap: reply code %d is unknown, Rejecting the request.", reply->code);
		packet->code = PW_AUTHENTICATION_REJECT;
		break;
	}

	return rcode;
}
