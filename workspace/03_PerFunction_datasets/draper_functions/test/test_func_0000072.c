find_previous_visible_provider (GList *provider)
{
	GList *l;

	for (l = provider; l != NULL; l = l->prev)
	{
		ProviderInfo *info = l->data;

		if (info->visible)
		{
			return l;
		}
	}

	return NULL;
}
