cpt_accept(MainInfo *min)
{
	P_Paths		*page = &the_page;
	const gchar	*text;
	gint		i;

	if(page->open && page->modified)
	{
		for(i = 0; i < PTID_NUM_PATHS; i++)
		{
			text = gtk_entry_get_text(GTK_ENTRY(page->path[i].path));
			if(strcmp(text, min->cfg.path.path[i]->str))
			{
				g_string_assign(min->cfg.path.path[i], text);
				switch((PathID) i)
				{
					case PTID_ICON:
						cfg_set_flags(CFLG_FLUSH_ICONS);
						break;
					default:
						break;
				}
			}
		}
		min->cfg.path.hideinfo = page->hideinfo;
		fut_check_hide(&min->gui->pane[0], NULL);
		cfg_set_flags(CFLG_RESCAN_BOTH);
		page->modified = FALSE;
	}
}
