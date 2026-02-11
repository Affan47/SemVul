process_eap_sim_challenge(EAP_HANDLER *handler, VALUE_PAIR *vps)
{
	struct eap_sim_server_state *ess;
	uint8_t srescat[EAPSIM_SRES_SIZE*3];
	uint8_t calcmac[EAPSIM_CALCMAC_SIZE];

	ess = (struct eap_sim_server_state *)handler->opaque;

	memcpy(srescat +(0*EAPSIM_SRES_SIZE), ess->keys.sres[0], EAPSIM_SRES_SIZE);
	memcpy(srescat +(1*EAPSIM_SRES_SIZE), ess->keys.sres[1], EAPSIM_SRES_SIZE);
	memcpy(srescat +(2*EAPSIM_SRES_SIZE), ess->keys.sres[2], EAPSIM_SRES_SIZE);


	if(eapsim_checkmac(vps, ess->keys.K_aut,
			   srescat, sizeof(srescat),
			   calcmac)) {
		DEBUG2("MAC check succeed\n");
	} else {
		int i, j;
		char macline[20*3];
		char *m = macline;

		j=0;
		for (i = 0; i < EAPSIM_CALCMAC_SIZE; i++) {
			if(j==4) {
			  *m++ = '_';
			  j=0;
			}
			j++;

			sprintf(m, "%02x", calcmac[i]);
			m = m + strlen(m);
		}
		DEBUG2("calculated MAC (%s) did not match", macline);
		return 0;
	}


	eap_sim_stateenter(handler, ess, eapsim_server_success);
	return 1;
}
