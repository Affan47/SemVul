pv_get_srcip(struct sip_msg *msg, pv_param_t *param,
		pv_value_t *res)
{
	str s;
	if(msg==NULL)
		return -1;

	s.s = ip_addr2a(&msg->rcv.src_ip);
	s.len = strlen(s.s);
	return pv_get_strval(msg, param, res, &s);
}
