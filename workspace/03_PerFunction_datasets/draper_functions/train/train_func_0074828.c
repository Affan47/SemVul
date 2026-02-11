set_default(struct ConfTable *ct)
{
	if (ct->flags & CONF_NO_REHASH && runflags & RF_REHASHING)
		return;

	switch (ct->type)
	{
		case CONF_UINT:
			*ct->un.uint_val.var = ct->un.uint_val.def;
			break;
		case CONF_DURATION:
			*ct->un.duration_val.var = ct->un.duration_val.def;
			break;
		case CONF_DUPSTR:
			if (*ct->un.dupstr_val.var)
				free(*ct->un.dupstr_val.var);
			*ct->un.dupstr_val.var = ct->un.dupstr_val.def ? sstrdup(ct->un.dupstr_val.def) : NULL;
			break;
		case CONF_BOOL:
			*ct->un.bool_val.var = ct->un.bool_val.def;
			break;
		case CONF_HANDLER:
		case CONF_SUBBLOCK:
			break;
	}
}
