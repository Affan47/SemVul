lrm_add_rsc (ll_lrm_t* lrm, const char* rsc_id, const char* class
, 	     const char* type, const char* provider, GHashTable* parameter)
{
	struct ha_msg* msg;


	if (NULL == rsc_id || RID_LEN <= strlen(rsc_id))	{
		cl_log(LOG_ERR, "lrm_add_rsc: wrong parameter rsc_id.");
		return HA_FAIL;
	}


	if (NULL == ch_cmd)	{
		cl_log(LOG_ERR, "lrm_add_rsc: ch_mod is null.");
		return HA_FAIL;
	}


	msg = create_lrm_addrsc_msg(rsc_id, class, type, provider, parameter);
	if ( NULL == msg) {
		cl_log(LOG_ERR, "%s(%d): failed to create a ADDSRC message "
			"with function create_lrm_addrsc_msg"
		,	__FUNCTION__, __LINE__);
		return HA_FAIL;
	}

	if (HA_OK != msg2ipcchan(msg,ch_cmd)) {
		ha_msg_del(msg);
		LOG_FAIL_SEND_MSG(ADDRSC, "ch_cmd");
		return HA_FAIL;
	}
	ha_msg_del(msg);

	if (HA_OK != get_ret_from_ch(ch_cmd)) {
		LOG_GOT_FAIL_RET(LOG_ERR, ADDRSC);
		return HA_FAIL;
	}

	return HA_OK;
}
