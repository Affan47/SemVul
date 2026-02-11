connman_technology_tethering_notify(struct connman_technology *technology,
							connman_bool_t enabled)
{
	GSList *list;

	DBG("technology %p enabled %u", technology, enabled);

	if (technology->tethering == enabled)
		return;

	technology->tethering = enabled;

	tethering_changed(technology);

	if (enabled == TRUE)
		__connman_tethering_set_enabled();
	else {
		for (list = technology_list; list; list = list->next) {
			struct connman_technology *other_tech = list->data;
			if (other_tech->tethering == TRUE)
				break;
		}
		if (list == NULL)
			__connman_tethering_set_disabled();
	}
}
