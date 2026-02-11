pv_set_bflags(struct sip_msg* msg, pv_param_t *param,
		int op, pv_value_t *val)
{
	if(msg==NULL || param==NULL)
	{
		LM_ERR("bad parameters\n");
		return -1;
	}

	if(val == NULL)
	{
		setb0flags(0);
		return 0;
	}

	if(!(val->flags&PV_VAL_INT))
	{
		LM_ERR("assigning non-int value to branch 0 flags\n");
		return -1;
	}

	setb0flags((unsigned int)val->ri);

	return 0;
}
