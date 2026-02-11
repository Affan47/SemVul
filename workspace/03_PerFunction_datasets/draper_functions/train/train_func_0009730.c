chanlist_destroy_widget (GtkWidget *wid, server *serv)
{
	custom_list_clear ((CustomList *)GET_MODEL (serv));
	chanlist_data_free (serv);

	if (serv->gui->chanlist_flash_tag)
	{
		g_source_remove (serv->gui->chanlist_flash_tag);
		serv->gui->chanlist_flash_tag = 0;
	}

	if (serv->gui->chanlist_tag)
	{
		g_source_remove (serv->gui->chanlist_tag);
		serv->gui->chanlist_tag = 0;
	}

#ifndef WIN32
	if (serv->gui->have_regex)
	{
		regfree (&serv->gui->chanlist_match_regex);
		serv->gui->have_regex = 0;
	}
#endif
}
