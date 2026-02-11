gfire_preferences_set(gfire_preferences *p_prefs, guint8 p_id, gboolean p_set)
{
	if(!p_prefs)
		return;


	GList *cur = p_prefs->prefs;
	while(cur)
	{
		gf_pref *pref = (gf_pref*)cur->data;
		if(pref->id == p_id)
		{
			if(p_set == gfire_preferences_get_default(p_id))
			{
				g_free(pref);
				p_prefs->prefs = g_list_delete_link(p_prefs->prefs, cur);
			}
			else
				pref->set = p_set;
			return;
		}
		cur = g_list_next(cur);
	}


	gf_pref *pref = g_malloc(sizeof(gf_pref));
	pref->id = p_id;
	pref->set = p_set;
	p_prefs->prefs = g_list_append(p_prefs->prefs, pref);
}
