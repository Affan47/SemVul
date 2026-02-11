process_reply(EAP_HANDLER *handler, tls_session_t *tls_session,
			 REQUEST *request, RADIUS_PACKET *reply)
{
	int rcode = RLM_MODULE_REJECT;
	VALUE_PAIR *vp;
	ttls_tunnel_t *t = tls_session->opaque;

	handler = handler;


	switch (reply->code) {
	case PW_AUTHENTICATION_ACK:
		RDEBUG("Got tunneled Access-Accept");

		rcode = RLM_MODULE_OK;


		vp = NULL;
		pairmove2(&vp, &reply->vps, PW_MSCHAP2_SUCCESS);
		if (vp) {
			RDEBUG("Got MS-CHAP2-Success, tunneling it to the client in a challenge.");
			rcode = RLM_MODULE_HANDLED;
			t->authenticated = TRUE;


			pairdelete(&reply->vps, ((311 << 16) | 7));
			pairdelete(&reply->vps, ((311 << 16) | 8));
			pairdelete(&reply->vps, ((311 << 16) | 16));
			pairdelete(&reply->vps, ((311 << 16) | 17));


			if (t->use_tunneled_reply) {
				t->accept_vps = reply->vps;
				reply->vps = NULL;
			}

		} else {


			pairmove2(&vp, &reply->vps, PW_EAP_MESSAGE);
			pairfree(&vp);
		}


		if (vp) {
			vp2diameter(request, tls_session, vp);
			pairfree(&vp);
		}


		if (t->use_tunneled_reply) {
			pairdelete(&reply->vps, PW_PROXY_STATE);
			pairadd(&request->reply->vps, reply->vps);
			reply->vps = NULL;
		}
		break;


	case PW_AUTHENTICATION_REJECT:
		RDEBUG("Got tunneled Access-Reject");
		rcode = RLM_MODULE_REJECT;
		break;


	case PW_ACCESS_CHALLENGE:
		RDEBUG("Got tunneled Access-Challenge");


		pairfree(&t->state);
		pairmove2(&t->state, &reply->vps, PW_STATE);


		vp = NULL;
		pairmove2(&vp, &reply->vps, PW_EAP_MESSAGE);


		pairmove2(&vp, &reply->vps, PW_REPLY_MESSAGE);


		if (vp) {
			vp2diameter(request, tls_session, vp);
			pairfree(&vp);
		}
		rcode = RLM_MODULE_HANDLED;
		break;

	default:
		RDEBUG("Unknown RADIUS packet type %d: rejecting tunneled user", reply->code);
		rcode = RLM_MODULE_INVALID;
		break;
	}

	return rcode;
}
