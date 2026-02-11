sysproc_get (int id)
{
	SYSPROC * s ;


	if (id < sysproc_maxid)
		return sysproc_list[id];


	if (sysproc_list == NULL)
	{


		for (s = sysprocs ; s->name ; s++)
		{
			if (s->id == 0) s->id = identifier_search_or_add(s->name) ;
			if (s->id > sysproc_maxid) sysproc_maxid = s->id;

			s->next = NULL;
		}


		sysproc_maxid = ((sysproc_maxid+1) & ~31) + 32;
		sysproc_list  = (SYSPROC * *) calloc (sysproc_maxid, sizeof(SYSPROC*));
		if (sysproc_list == NULL) abort();


		for (s = sysprocs ; s->name ; s++)
		{
			if (s->id > 0)
			{
				s->next = sysproc_list[s->id];
				sysproc_list[s->id] = s;
			}
		}

		if (id < sysproc_maxid)
			return sysproc_list[id];
	}
	return NULL;
}
