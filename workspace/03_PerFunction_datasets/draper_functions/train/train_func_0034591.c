conftable_get_conf_handler(struct ConfTable *ct)
{
	return ct->type == CONF_HANDLER ? ct->un.handler : NULL;
}
