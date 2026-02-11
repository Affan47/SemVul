recurse_get(char *result, const char *ref, int kind,
		int level, int build)
{

	char buffer[FM_BUFFER_SIZE];
	strncpy(buffer, ref, FM_BUFFER_SIZE);


	char *obj = (char *)strstr(ref, FM_DEREF_TOKEN);


	if(!obj)
	{
		int res;
		snprintf(buffer, FM_BUFFER_SIZE, "%s", ref);
		buffer[FM_BUFFER_SIZE-1] = 0;
#if 0
		{
			for(int s=0; s<level; ++s)
				log_printf(DLOG, "  ");
		}
		log_printf(DLOG, "('%s') (no key!)\n", buffer);
		log_printf(DLOG, "Trying '%s'...", ref);
#endif
		sys_slashes(buffer);
		res = try_get(buffer, kind);
		if(build && res)
			add_object(buffer, kind);
		if(res && !build)
		{
			strncpy(result, buffer, FM_BUFFER_SIZE);
			return 1;
		}
		else
			return 0;
	}

	char kclass[9];
	int len = obj - ref;
	obj += 2;
	if(len > 8)
		len = 8;
	memcpy(kclass, ref, len);
	kclass[len] = 0;

	fm_key_t *k = NULL;
	int hits = 0;
	while( (k = getkey(k, kclass)) )
	{
		++hits;
		snprintf(buffer, FM_BUFFER_SIZE, "%s/%s", k->path, obj);
		buffer[FM_BUFFER_SIZE-1] = 0;
#if 0
		{
			for(int s=0; s<level; ++s)
				log_printf(DLOG, "  ");
		}
		log_printf(DLOG, "('%s')\n", buffer);
		{
			for(int s=0; s<level; ++s)
				log_printf(DLOG, "  ");
		}
#endif
		int res;
		char *dt = strstr(buffer, FM_DEREF_TOKEN);
		if(dt)
		{

			if(dt[2] == '/')
				strdel(dt + 2, 1);
			res = recurse_get(buffer, buffer, kind, level + 1,
					build);
		}
		else
		{


			sys_slashes(buffer);
			res = try_get(buffer, kind);
			if(build && res)
				add_object(buffer, kind);
		}
		if(res && !build)
		{
			strncpy(result, buffer, FM_BUFFER_SIZE);
			return 1;
		}
	}
#if 0
	if(!hits)
	{
		for(int s=0; s<level; ++s)
			log_printf(DLOG, "  ");
		log_printf(DLOG, "No paths registered for '%s'!\n", kclass);
	}
#endif
	return 0;
}
