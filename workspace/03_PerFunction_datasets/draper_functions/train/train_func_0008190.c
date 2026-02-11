on_msg_set_lrmd_param(lrmd_client_t* client, struct ha_msg* msg)
{
	const char *name, *value;

	CHECK_ALLOCATED(client, "client", HA_FAIL);
	CHECK_ALLOCATED(msg, "message", HA_FAIL);

	name = ha_msg_value(msg,F_LRM_LRMD_PARAM_NAME);
	value = ha_msg_value(msg,F_LRM_LRMD_PARAM_VAL);
	if (!name || !value) {
		lrmd_log(LOG_ERR, "%s: no parameter defined"
			, __FUNCTION__);
		return HA_FAIL;
	}
	return set_lrmd_param(name,value);
}
