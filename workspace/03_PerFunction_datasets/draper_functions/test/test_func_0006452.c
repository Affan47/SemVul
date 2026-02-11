providers_cycle_forward (GList *all_providers,
			 GList *position,
			 gint   num)
{
	GList *l = position;
	gint i;

	if (all_providers == NULL || all_providers->next == NULL)
	{
		return NULL;
	}

	for (i = 0; i < num; i++)
	{
		l = l == NULL ? all_providers : l->next;
	}

	return l;
}
