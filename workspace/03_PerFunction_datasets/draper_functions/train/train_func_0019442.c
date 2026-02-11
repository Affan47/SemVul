subblock_handler(config_entry_t *ce, mowgli_list_t *entries)
{
	mowgli_node_t *tn;
	struct ConfTable *ct = NULL;

	MOWGLI_ITER_FOREACH(tn, entries->head)
	{
		ct = tn->data;

		set_default(ct);
	}

	for (ce = ce->ce_entries; ce; ce = ce->ce_next)
	{
		MOWGLI_ITER_FOREACH(tn, entries->head)
		{
			ct = tn->data;

			if (!strcasecmp(ct->name, ce->ce_varname))
			{
				process_configentry(ct, ce);
				break;
			}
		}

		if (ct == NULL)
			conf_report_warning(ce, "invalid configuration option");
	}
	return 0;
}
