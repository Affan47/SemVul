provider_has_info (ProviderInfo *provider_info)
{
	GList *l;

	for (l = provider_info->proposals->head; l != NULL; l = l->next)
	{
		ProposalInfo *proposal_info = l->data;

		if (proposal_info->completion_proposal == NULL)
		{
			continue;
		}

		if (proposal_has_info (provider_info->completion_provider,
				       proposal_info->completion_proposal))
		{
			return TRUE;
		}
	}

	return FALSE;
}
