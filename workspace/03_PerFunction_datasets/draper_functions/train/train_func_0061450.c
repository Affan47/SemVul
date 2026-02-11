eap_sim_sendstart(EAP_HANDLER *handler)
{
	VALUE_PAIR **vps, *newvp;
	uint16_t *words;
	struct eap_sim_server_state *ess;

	rad_assert(handler->request != NULL);
	rad_assert(handler->request->reply);

	ess = (struct eap_sim_server_state *)handler->opaque;


	vps = &handler->request->reply->vps;

	rad_assert(vps != NULL);


	newvp = paircreate(ATTRIBUTE_EAP_SIM_BASE+PW_EAP_SIM_VERSION_LIST,
			PW_TYPE_OCTETS);
	words = (uint16_t *)newvp->vp_strvalue;
	newvp->length = 3*sizeof(uint16_t);
	words[0] = htons(1*sizeof(uint16_t));
	words[1] = htons(EAP_SIM_VERSION);
	words[2] = 0;
	pairadd(vps, newvp);


	newvp = paircreate(ATTRIBUTE_EAP_ID, PW_TYPE_INTEGER);
	newvp->vp_integer = ess->sim_id++;
	pairreplace(vps, newvp);


	ess->keys.versionlistlen = 2;
	memcpy(ess->keys.versionlist, words+1, ess->keys.versionlistlen);


	newvp = paircreate(ATTRIBUTE_EAP_SIM_BASE+PW_EAP_SIM_FULLAUTH_ID_REQ,
			   PW_TYPE_OCTETS);
	newvp->length = 2;
	newvp->vp_strvalue[0]=0;
	newvp->vp_strvalue[0]=1;
	pairadd(vps, newvp);


	newvp = paircreate(ATTRIBUTE_EAP_SIM_SUBTYPE, PW_TYPE_INTEGER);
	newvp->vp_integer = eapsim_start;
	pairreplace(vps, newvp);

	return 1;
}
