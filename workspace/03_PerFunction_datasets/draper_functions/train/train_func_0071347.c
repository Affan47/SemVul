cmc_field_add_boolean(CmdCfg *cmc, const gchar *name, const gchar *desc, gsize offset)
{
	if(cmc != NULL)
		field_add(cmc, field_new(CFT_BOOLEAN, name, desc, offset));
}
