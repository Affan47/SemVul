pv_parse_scriptvar_name(pv_spec_p sp, str *in)
{
	if(in==NULL || in->s==NULL || sp==NULL)
		return -1;

	sp->pvp.pvn.type = PV_NAME_PVAR;
	sp->pvp.pvn.u.dname = (void*)add_var(in);
	if(sp->pvp.pvn.u.dname==NULL)
	{
		LM_ERR("cannot register var [%.*s]\n", in->len, in->s);
		return -1;
	}
	return 0;
}
