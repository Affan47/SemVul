do_acctlog_acct(void *instance, REQUEST *request)
{
	rlm_acctlog_t *inst;
	VALUE_PAIR *pair;

	char    logstr[1024];
	int     acctstatustype = 0;


	inst = (rlm_acctlog_t*) instance;

    if ((pair = pairfind(request->packet->vps, PW_ACCT_STATUS_TYPE)) != NULL) {
        acctstatustype = pair->vp_integer;
    } else {
        radius_xlat(logstr, sizeof(logstr), "packet has no accounting status type. [user '%{User-Name}', nas '%{NAS-IP-Address}']", request, NULL);
        radlog(L_ERR, "rlm_acctlog (%s)", logstr);
        return RLM_MODULE_INVALID;
    }

	switch (acctstatustype) {
		case PW_STATUS_START:
			radius_xlat(logstr, sizeof(logstr), inst->acctstart, request, NULL);
		break;
		case PW_STATUS_STOP:
			radius_xlat(logstr, sizeof(logstr), inst->acctstop, request, NULL);
		break;
		case PW_STATUS_ALIVE:
			radius_xlat(logstr, sizeof(logstr), inst->acctupdate, request, NULL);
		break;
		case PW_STATUS_ACCOUNTING_ON:
			radius_xlat(logstr, sizeof(logstr), inst->accton, request, NULL);
		break;
		case PW_STATUS_ACCOUNTING_OFF:
			radius_xlat(logstr, sizeof(logstr), inst->acctoff, request, NULL);
		break;

	}

	if (strlen(logstr))
		radlog(L_ACCT,"%s", logstr);

	return RLM_MODULE_OK;
}
