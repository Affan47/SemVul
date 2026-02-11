gfire_clan_create(guint32 p_clanid, const gchar *p_longName, const gchar *p_shortName, gboolean p_createGroup)
{
	gfire_clan *ret = g_malloc0(sizeof(gfire_clan));
	if(!ret)
		goto error;

	ret->id = p_clanid;

	if(p_longName)
	{
		ret->long_name = g_strdup(p_longName);
		if(!ret->long_name)
		{
			gfire_clan_free(ret);
			goto error;
		}
	}

	if(p_shortName)
	{
		ret->short_name = g_strdup(p_shortName);
		if(!ret->short_name)
		{
			gfire_clan_free(ret);
			goto error;
		}
	}

	if(p_createGroup)
		gfire_clan_create_group(ret);

	return ret;

error:
	purple_debug(PURPLE_DEBUG_ERROR, "gfire", "gfire_clan_create: Out of memory!\n");
	return NULL;
}
