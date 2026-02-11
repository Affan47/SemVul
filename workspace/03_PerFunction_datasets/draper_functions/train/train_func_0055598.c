eap_sim_authenticate(void *arg, EAP_HANDLER *handler)
{
	struct eap_sim_server_state *ess;
	VALUE_PAIR *vp, *vps;
	enum eapsim_subtype subtype;
	int success;

	arg = arg;

	ess = (struct eap_sim_server_state *)handler->opaque;


	vps = handler->request->packet->vps;

	success= unmap_eapsim_basictypes(handler->request->packet,
					 handler->eap_ds->response->type.data,
					 handler->eap_ds->response->type.length);

	if(!success) {
	  return 0;
	}


	if((vp = pairfind(vps, ATTRIBUTE_EAP_SIM_SUBTYPE)) == NULL)
	{
		DEBUG2("   no subtype attribute was created, message dropped");
		return 0;
	}
	subtype = vp->vp_integer;


	if (subtype == eapsim_client_error) {
		return 0;
	}

	switch(ess->state) {
	case eapsim_server_start:
		switch(subtype) {
		default:


			eap_sim_stateenter(handler, ess, eapsim_server_start);
			return 1;

		case eapsim_start:


			return process_eap_sim_start(handler, vps);
		}
		break;
	case eapsim_server_challenge:
		switch(subtype) {
		default:


			eap_sim_stateenter(handler, ess, eapsim_server_challenge);
			return 1;

		case eapsim_challenge:


			return process_eap_sim_challenge(handler, vps);
		}
		break;

	default:


		DEBUG2("  illegal-unknown state reached in eap_sim_authenticate\n");
		rad_assert(0 == 1);
 	}

	return 0;
}
