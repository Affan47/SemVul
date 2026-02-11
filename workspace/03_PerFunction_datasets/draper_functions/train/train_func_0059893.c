mission_campaign_maybe_add(char *filename)
{
	char name[NAME_LENGTH];
	char *desc = NULL;
	int type, max_players;

	if ( mission_campaign_get_info( filename, name, &type, &max_players, &desc) ) {

		if (campaign_is_ignored(filename)) {
			return 0;
		}

		if ( !MC_multiplayer && (type == CAMPAIGN_TYPE_SINGLE) ) {
			Campaign_names[Num_campaigns] = vm_strdup(name);

			if (MC_desc)
				Campaign_descs[Num_campaigns] = desc;

			Num_campaigns++;

			return 1;
		}
	}

	if (desc != NULL)
		vm_free(desc);

	return 0;
}
