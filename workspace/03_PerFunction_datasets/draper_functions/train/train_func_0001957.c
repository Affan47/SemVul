check_valid_entries(void)
{
	rb_dlink_node *ptr, *xptr;
	conf_t *conf;
	confentry_t *entry;
	valid_block_t *vt;
	int ret = 0;
	RB_DLINK_FOREACH(ptr, conflist.head)
	{
		conf = ptr->data;
		vt = find_valid_block(conf->confname);
		if(vt == NULL)
		{
			conf_report_warning_nl("Invalid block: %s at %s:%d", conf->confname,
					       conf->filename, conf->line);

			continue;
		}
		if(vt->needsub && conf->subname == NULL)
		{
			conf_report_error_nl("Block %s at %s:%d requires a name", conf->confname,
					     conf->filename, conf->line);
			ret++;
			continue;
		}
		if(!vt->needsub && conf->subname != NULL)
		{
			conf_report_warning_nl
				("Block %s at %s:%d does not require a name, but has one",
				 conf->confname, conf->filename, conf->line);

			continue;
		}
		RB_DLINK_FOREACH(xptr, conf->entries.head)
		{
			entry = xptr->data;
			if(entry->entryname == NULL)
				continue;
			if(!check_valid_entry(vt, conf, entry))
			{
				ret++;
			}
		}

	}
	return ret;

}
