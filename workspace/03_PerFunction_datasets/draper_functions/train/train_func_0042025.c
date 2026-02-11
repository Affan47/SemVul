c_operclass(config_entry_t *ce)
{
	operclass_t *operclass;
	char *name;
	char *privs = NULL, *newprivs;
	int flags = 0;

	if (ce->ce_vardata == NULL)
	{
		conf_report_warning(ce, "no parameter for configuration option");
		return 0;
	}

	name = ce->ce_vardata;

	for (ce = ce->ce_entries; ce; ce = ce->ce_next)
	{
		if (!strcasecmp("PRIVS", ce->ce_varname))
		{
			if (ce->ce_vardata == NULL && ce->ce_entries == NULL)
				conf_report_warning(ce, "no parameter for configuration option");

			if (ce->ce_vardata != NULL)
			{
				if (privs == NULL)
					privs = sstrdup(ce->ce_vardata);
				else
				{
					newprivs = smalloc(strlen(privs) + 1 + strlen(ce->ce_vardata) + 1);
					strcpy(newprivs, privs);
					strcat(newprivs, " ");
					strcat(newprivs, ce->ce_vardata);
					free(privs);
					privs = newprivs;
				}
			}
			else
			{
				config_entry_t *conf_p;


				for (conf_p = ce->ce_entries; conf_p; conf_p = conf_p->ce_next)
				{
					if (privs == NULL)
						privs = sstrdup(conf_p->ce_varname);
					else
					{
						newprivs = smalloc(strlen(privs) + 1 + strlen(conf_p->ce_varname) + 1);
						strcpy(newprivs, privs);
						strcat(newprivs, " ");
						strcat(newprivs, conf_p->ce_varname);
						free(privs);
						privs = newprivs;
					}
				}
			}
		}
		else if (!strcasecmp("EXTENDS", ce->ce_varname))
		{
			if (ce->ce_vardata == NULL)
			{
				conf_report_warning(ce, "no parameter for configuration option");
				continue;
			}
			operclass_t *parent = operclass_find(ce->ce_vardata);
			if (parent == NULL)
			{
				conf_report_warning(ce, "nonexistent extends operclass %s for operclass %s", ce->ce_vardata, name);
				continue;
			}

			if (privs == NULL)
				privs = sstrdup(parent->privs);
			else
			{
				newprivs = smalloc(strlen(privs) + 1 + strlen(parent->privs) + 1);
				strcpy(newprivs, privs);
				strcat(newprivs, " ");
				strcat(newprivs, parent->privs);
				free(privs);
				privs = newprivs;
			}
		}
		else if (!strcasecmp("NEEDOPER", ce->ce_varname))
			flags |= OPERCLASS_NEEDOPER;
		else
		{
			conf_report_warning(ce, "Invalid configuration option");
			continue;
		}
	}

	operclass = operclass_add(name, privs ? privs : "");
	if (operclass != NULL)
		operclass->flags |= flags;
	free(privs);
	return 0;
}
