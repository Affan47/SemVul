status_change_requires_provider_change (GList            *provider_list,
                                        GcMasterProvider *current_provider,
                                        GcMasterProvider *changed_provider,
                                        GeoclueStatus     status)
{
	if (!provider_list) {
		return FALSE;

	} else if (current_provider == NULL) {
		return (status == GEOCLUE_STATUS_AVAILABLE);

	} else if (current_provider == changed_provider) {
		return (status != GEOCLUE_STATUS_AVAILABLE);

	}else if (status != GEOCLUE_STATUS_AVAILABLE) {
		return FALSE;

	}

	while (provider_list) {
		GcMasterProvider *p = provider_list->data;
		if (p == current_provider) {

			return FALSE;
		}
		if (p == changed_provider) {

			return (status == GEOCLUE_STATUS_AVAILABLE);
		}
		provider_list = provider_list->next;
	}
	return FALSE;
}
