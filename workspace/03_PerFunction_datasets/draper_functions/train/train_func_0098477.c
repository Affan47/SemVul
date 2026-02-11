c_operator(config_entry_t *ce)
{
	char *name;
	char *password = NULL;
	operclass_t *operclass = NULL;
	config_entry_t *topce;

	if (ce->ce_vardata == NULL)
	{
		conf_report_warning(ce, "no parameter for configuration option");
		return 0;
	}

	topce = ce;
	name = ce->ce_vardata;

	for (ce = ce->ce_entries; ce; ce = ce->ce_next)
	{
		if (!strcasecmp("OPERCLASS", ce->ce_varname))
		{
			if (ce->ce_vardata == NULL)
			{
				conf_report_warning(ce, "no parameter for configuration option");
				return 0;
			}

			operclass = operclass_find(ce->ce_vardata);
			if (operclass == NULL)
				conf_report_warning(ce, "invalid operclass %s for operator %s",
						ce->ce_vardata, name);
		}
		else if (!strcasecmp("PASSWORD", ce->ce_varname))
		{
			if (ce->ce_vardata == NULL)
			{
				conf_report_warning(ce, "no parameter for configuration option");
				return 0;
			}

			password = ce->ce_vardata;
		}
		else
		{
			conf_report_warning(ce, "Invalid configuration option");
			continue;
		}
	}

	if (operclass != NULL)
		soper_add(name, operclass->name, SOPER_CONF, password);
	else
		conf_report_warning(topce, "skipping operator %s because of bad/missing parameters",
						name);
	return 0;
}
