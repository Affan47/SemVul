rsc_cancel_op (lrm_rsc_t* rsc, int call_id)
{
	int rc;
	struct ha_msg* msg = NULL;


	if (NULL == ch_cmd)	{
		cl_log(LOG_ERR, "rsc_cancel_op: ch_mod is null.");
		return HA_FAIL;
	}

	if (NULL == rsc) {
		cl_log(LOG_ERR, "rsc_cancel_op: parameter rsc is null.");
		return HA_FAIL;
	}

	msg = create_lrm_rsc_msg(rsc->id,CANCELOP);
	if (NULL == msg) {
		LOG_FAIL_create_lrm_rsc_msg(CANCELOP);
		return HA_FAIL;
	}
	if (HA_OK != ha_msg_add_int(msg, F_LRM_CALLID, call_id))	{
		LOG_BASIC_ERROR("ha_msg_add_int");
		ha_msg_del(msg);
		return HA_FAIL;
	}


	if (HA_OK != msg2ipcchan(msg,ch_cmd)) {
		ha_msg_del(msg);
		LOG_FAIL_SEND_MSG(CANCELOP, "ch_cmd");
		return HA_FAIL;
	}
	ha_msg_del(msg);

	rc = get_ret_from_ch(ch_cmd);

	return rc;
}
