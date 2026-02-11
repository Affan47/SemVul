pv_get_ouri(struct sip_msg *msg, pv_param_t *param,
		pv_value_t *res)
{
	if(msg==NULL || res==NULL)
		return -1;

	if(msg->first_line.type == SIP_REPLY)
		return pv_get_null(msg, param, res);

	if(msg->parsed_orig_ruri_ok==0
			 && parse_orig_ruri(msg)<0)
	{
		LM_ERR("failed to parse the R-URI\n");
		return pv_get_null(msg, param, res);
	}
	return pv_get_strval(msg, param, res, &msg->first_line.u.request.uri);
}
