pv_get_dsturi(struct sip_msg *msg, pv_param_t *param,
		pv_value_t *res)
{
	if(msg==NULL)
		return -1;

	if (msg->dst_uri.s == NULL) {
		LM_DBG("no destination URI\n");
		return pv_get_null(msg, param, res);
	}

	return pv_get_strval(msg, param, res, &msg->dst_uri);
}
