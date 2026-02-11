mission_campaign_free_list()
{
	int i;

	if ( !Campaign_names_inited )
		return;

	for (i = 0; i < Num_campaigns; i++) {
		if (Campaign_names[i] != NULL) {
			vm_free(Campaign_names[i]);
			Campaign_names[i] = NULL;
		}

		if (Campaign_file_names[i] != NULL) {
			vm_free(Campaign_file_names[i]);
			Campaign_file_names[i] = NULL;
		}

		if (Campaign_descs[i] != NULL) {
			vm_free(Campaign_descs[i]);
			Campaign_descs[i] = NULL;
		}
	}

	Num_campaigns = 0;
	Campaign_names_inited = 0;
}
