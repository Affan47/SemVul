respond_eap_sim(RADIUS_PACKET *req,
			   RADIUS_PACKET *resp)
{
	enum eapsim_clientstates state, newstate;
	enum eapsim_subtype subtype;
	VALUE_PAIR *vp, *statevp, *radstate, *eapid;
	char statenamebuf[32], subtypenamebuf[32];

	if ((radstate = paircopy2(req->vps, PW_STATE)) == NULL)
	{
		return 0;
	}

	if ((eapid = paircopy2(req->vps, ATTRIBUTE_EAP_ID)) == NULL)
	{
		return 0;
	}


	if((statevp = pairfind(resp->vps, ATTRIBUTE_EAP_SIM_STATE)) == NULL)
	{

		statevp = paircreate(ATTRIBUTE_EAP_SIM_STATE, PW_TYPE_INTEGER);
		statevp->vp_integer = eapsim_client_init;
		pairreplace(&(resp->vps), statevp);
	}
	state = statevp->vp_integer;


	unmap_eapsim_types(req);

	if((vp = pairfind(req->vps, ATTRIBUTE_EAP_SIM_SUBTYPE)) == NULL)
	{
		return 0;
	}
	subtype = vp->vp_integer;


	switch(state) {
	case eapsim_client_init:
		switch(subtype) {
		case eapsim_start:
			newstate = process_eap_start(req, resp);
			break;

		case eapsim_challenge:
		case eapsim_notification:
		case eapsim_reauth:
		default:
			fprintf(stderr, "radeapclient: sim in state %s message %s is illegal. Reply dropped.\n",
				sim_state2name(state, statenamebuf, sizeof(statenamebuf)),
				sim_subtype2name(subtype, subtypenamebuf, sizeof(subtypenamebuf)));

			return 0;
		}
		break;

	case eapsim_client_start:
		switch(subtype) {
		case eapsim_start:

			newstate = process_eap_start(req, resp);
			break;

		case eapsim_challenge:
			newstate = process_eap_challenge(req, resp);
			break;

		default:
			fprintf(stderr, "radeapclient: sim in state %s message %s is illegal. Reply dropped.\n",
				sim_state2name(state, statenamebuf, sizeof(statenamebuf)),
				sim_subtype2name(subtype, subtypenamebuf, sizeof(subtypenamebuf)));

			return 0;
		}
		break;


	default:
		fprintf(stderr, "radeapclient: sim in illegal state %s\n",
			sim_state2name(state, statenamebuf, sizeof(statenamebuf)));
		return 0;
	}


	pairreplace(&(resp->vps), eapid);


	map_eapsim_types(resp);


	pairreplace(&(resp->vps), radstate);

	statevp->vp_integer = newstate;
	return 1;
}
