map_eap_types(RADIUS_PACKET *req)
{
	VALUE_PAIR *vp, *vpnext;
	int id, eapcode;
	EAP_PACKET ep;
	int eap_type;

	vp = pairfind(req->vps, ATTRIBUTE_EAP_ID);
	if(vp == NULL) {
		id = ((int)getpid() & 0xff);
	} else {
		id = vp->vp_integer;
	}

	vp = pairfind(req->vps, ATTRIBUTE_EAP_CODE);
	if(vp == NULL) {
		eapcode = PW_EAP_REQUEST;
	} else {
		eapcode = vp->vp_integer;
	}


	for(vp = req->vps; vp != NULL; vp = vpnext) {

		vpnext = vp->next;

		if(vp->attribute >= ATTRIBUTE_EAP_BASE &&
		   vp->attribute < ATTRIBUTE_EAP_BASE+256) {
			break;
		}
	}

	if(vp == NULL) {
		return;
	}

	eap_type = vp->attribute - ATTRIBUTE_EAP_BASE;

	switch(eap_type) {
	case PW_EAP_IDENTITY:
	case PW_EAP_NOTIFICATION:
	case PW_EAP_NAK:
	case PW_EAP_MD5:
	case PW_EAP_OTP:
	case PW_EAP_GTC:
	case PW_EAP_TLS:
	case PW_EAP_LEAP:
	case PW_EAP_TTLS:
	case PW_EAP_PEAP:
	default:


		pairdelete(&req->vps, PW_EAP_MESSAGE);

		memset(&ep, 0, sizeof(ep));
		ep.code = eapcode;
		ep.id   = id;
		ep.type.type = eap_type;
		ep.type.length = vp->length;
		ep.type.data = malloc(vp->length);
		memcpy(ep.type.data,vp->vp_octets, vp->length);
		eap_basic_compose(req, &ep);
	}
}
