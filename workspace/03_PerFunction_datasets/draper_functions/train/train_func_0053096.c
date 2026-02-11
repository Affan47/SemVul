pv_parse_ct_name(pv_spec_p sp, str *in)
{
	if (sp==NULL)
		return -1;

	sp->pvp.pvn.type = PV_NAME_INTSTR;
	sp->pvp.pvn.u.isname.type = 0;

	if (in==NULL || in->s==NULL || in->len==0) {
		sp->pvp.pvn.u.isname.name.n = 0;
	} else
	if (in->len==CT_NAME_LEN &&
	strncasecmp(in->s, CT_NAME_S, CT_NAME_LEN)==0 ) {
		sp->pvp.pvn.u.isname.name.n = CT_NAME_ID;
	} else
	if (in->len==CT_URI_LEN &&
	strncasecmp(in->s, CT_URI_S, CT_URI_LEN)==0 ) {
		sp->pvp.pvn.u.isname.name.n = CT_URI_ID;
	} else
	if (in->len==CT_Q_LEN &&
	strncasecmp(in->s, CT_Q_S, CT_Q_LEN)==0 ) {
		sp->pvp.pvn.u.isname.name.n = CT_Q_ID;
	} else
	if (in->len==CT_EXPIRES_LEN &&
	strncasecmp(in->s, CT_EXPIRES_S, CT_EXPIRES_LEN)==0 ) {
		sp->pvp.pvn.u.isname.name.n = CT_EXPIRES_ID;
	} else
	if (in->len==CT_METHODS_LEN &&
	strncasecmp(in->s, CT_METHODS_S, CT_METHODS_LEN)==0 ) {
		sp->pvp.pvn.u.isname.name.n = CT_METHODS_ID;
	} else
	if (in->len==CT_RECEIVED_LEN &&
	strncasecmp(in->s, CT_RECEIVED_S, CT_RECEIVED_LEN)==0 ) {
		sp->pvp.pvn.u.isname.name.n = CT_RECEIVED_ID;
	} else
	if (in->len==CT_PARAMS_LEN &&
	strncasecmp(in->s, CT_PARAMS_S, CT_PARAMS_LEN)==0 ) {
		sp->pvp.pvn.u.isname.name.n = CT_PARAMS_ID;
	} else {
		LM_ERR("unsupported CT field <%.*s>\n",in->len,in->s);
		return -1;
	}

	return 0;
}
