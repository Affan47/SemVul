update_battery_panels(void)
	{
	GList		*list;
	Battery		*bat;

	for (list = battery_list; list; list = list->next)
		{
		bat = (Battery *) list->data;
		if (bat->enabled)
			update_battery_panel(bat);
		}
	}
