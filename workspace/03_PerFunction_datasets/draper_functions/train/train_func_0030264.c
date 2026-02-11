pv_set_force_sock(struct sip_msg* msg, pv_param_t *param,
		int op, pv_value_t *val)
{
	struct socket_info *si;
	int port, proto;
	str host;

	if(msg==NULL || param==NULL)
	{
		LM_ERR("bad parameters\n");
		return -1;
	}

	if(val==NULL)
	{
		msg->force_send_socket = NULL;
		return 0;
	}

	if(!(val->flags&PV_VAL_STR) || val->rs.len<=0)
	{
		LM_ERR("str value required to set the force send sock\n");
		goto error;
	}

	if (parse_phostport(val->rs.s, val->rs.len, &host.s, &host.len, &port, &proto) < 0)
	{
		LM_ERR("invalid socket specification\n");
		goto error;
	}
	set_sip_defaults( port, proto);
	si = grep_sock_info(&host, (unsigned short)port, (unsigned short)proto);
	if (si!=NULL)
	{
		msg->force_send_socket = si;
	} else {
		LM_WARN("no socket found to match [%.*s]\n",
				val->rs.len, val->rs.s);
	}

	return 0;
error:
	return -1;
}
