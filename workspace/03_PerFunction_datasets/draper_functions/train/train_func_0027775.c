ipvs_mt_parse(struct xt_option_call *cb)
{
	struct xt_ipvs_mtinfo *data = cb->data;

	xtables_option_parse(cb);
	switch (cb->entry->id) {
	case O_VPROTO:
		data->l4proto = cb->val.protocol;
		break;
	case O_VADDR:
		memcpy(&data->vaddr, &cb->val.haddr, sizeof(cb->val.haddr));
		memcpy(&data->vmask, &cb->val.hmask, sizeof(cb->val.hmask));
		break;
	case O_VDIR:
		if (strcasecmp(cb->arg, "ORIGINAL") == 0) {
			data->bitmask |= XT_IPVS_DIR;
			data->invert   &= ~XT_IPVS_DIR;
		} else if (strcasecmp(cb->arg, "REPLY") == 0) {
			data->bitmask |= XT_IPVS_DIR;
			data->invert  |= XT_IPVS_DIR;
		} else {
			xtables_param_act(XTF_BAD_VALUE,
					  "ipvs", "--vdir", cb->arg);
		}
		break;
	case O_VMETHOD:
		if (strcasecmp(cb->arg, "GATE") == 0)
			data->fwd_method = IP_VS_CONN_F_DROUTE;
		else if (strcasecmp(cb->arg, "IPIP") == 0)
			data->fwd_method = IP_VS_CONN_F_TUNNEL;
		else if (strcasecmp(cb->arg, "MASQ") == 0)
			data->fwd_method = IP_VS_CONN_F_MASQ;
		else
			xtables_param_act(XTF_BAD_VALUE,
					  "ipvs", "--vmethod", cb->arg);
		break;
	}
	data->bitmask |= 1 << cb->entry->id;
	if (cb->invert)
		data->invert |= 1 << cb->entry->id;
}
