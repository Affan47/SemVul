register_top_confs(void)
{
	CONF_CB *func;
	rb_dlink_node *ptr, *xptr, *yptr;
	struct topconf *top;
	conf_t *conf;
	confentry_t *entry;
	struct conf_items *tab;

	RB_DLINK_FOREACH(ptr, toplist.head)
	{
		top = ptr->data;
		RB_DLINK_FOREACH(xptr, conflist.head)
		{
			conf = xptr->data;
			if(strcasecmp(conf->confname, top->tc_name))
				continue;

			if(top->start_func != NULL)
				top->start_func(conf);
			RB_DLINK_FOREACH(yptr, conf->entries.head)
			{
				entry = yptr->data;
				tab = find_item(entry->entryname, top->itemtable);
				if(tab == NULL)
					continue;
				if(tab->cb_func == NULL)
					func = conf_set_generic_value_cb;
				else
					func = tab->cb_func;

				func(entry, conf, tab);
			}
			if(top->end_func != NULL)
				top->end_func(conf);
		}
	}
}
