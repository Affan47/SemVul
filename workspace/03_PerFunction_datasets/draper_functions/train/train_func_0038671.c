amp_create_property_list (GList **list, AmpPropertyInfo *properties)
{
	if (*list == NULL)
	{
		AmpPropertyInfo *info;
		AnjutaProjectPropertyInfo *link = NULL;

		for (info = properties; info->base.name != NULL; info++)
		{
			info->link = link;
			*list = g_list_prepend (*list, info);
			link = info->flags & AM_PROPERTY_DISABLE_FOLLOWING ? (AnjutaProjectPropertyInfo *)info : NULL;
			info->base.default_value = amp_property_new (NULL, 0, 0, info->value, NULL);
			info->base.default_value->info = (AnjutaProjectPropertyInfo *)info;
		}
		*list = g_list_reverse (*list);
	}

	return *list;
}
