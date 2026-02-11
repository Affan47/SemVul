ctp_accept(MainInfo *min)
{
	P_Types	*page = &the_page;
	GList	*iter;

	if(page->modified)
	{
		for(iter = min->cfg.type; iter != NULL; iter = g_list_next(iter))
			typ_type_destroy(iter->data);
		g_list_free(min->cfg.type);
		min->cfg.type = page->type;
		page->type	= NULL;
		page->modified	= FALSE;
		cfg_set_flags(CFLG_RESCAN_LEFT | CFLG_RESCAN_RIGHT);
	}
}
