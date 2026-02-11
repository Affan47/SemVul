atl1e_validate_option(int *value, struct atl1e_option *opt,
				 struct atl1e_adapter *adapter)
{
	if (*value == OPTION_UNSET) {
		*value = opt->def;
		return 0;
	}

	switch (opt->type) {
	case enable_option:
		switch (*value) {
		case OPTION_ENABLED:
			netdev_info(adapter->netdev,
				    "%s Enabled\n", opt->name);
			return 0;
		case OPTION_DISABLED:
			netdev_info(adapter->netdev,
				    "%s Disabled\n", opt->name);
			return 0;
		}
		break;
	case range_option:
		if (*value >= opt->arg.r.min && *value <= opt->arg.r.max) {
			netdev_info(adapter->netdev, "%s set to %i\n",
				    opt->name, *value);
			return 0;
		}
		break;
	case list_option:{
			int i;
			struct atl1e_opt_list *ent;

			for (i = 0; i < opt->arg.l.nr; i++) {
				ent = &opt->arg.l.p[i];
				if (*value == ent->i) {
					if (ent->str[0] != '\0')
						netdev_info(adapter->netdev,
							    "%s\n", ent->str);
					return 0;
				}
			}
			break;
		}
	default:
		BUG();
	}

	netdev_info(adapter->netdev, "Invalid %s specified (%i) %s\n",
		    opt->name, *value, opt->err);
	*value = opt->def;
	return -1;
}
