oscar_find_account_with_ela(const char *handle,
	eb_local_account *ela, gint should_update)
{
	eb_account *result = NULL;

	result = find_account_with_ela(aim_normalize(handle), ela);


	if (!result) {
		struct eb_aim_local_account_data *alad =
			(struct eb_aim_local_account_data *)ela->
			protocol_local_account_data;
		LList *node = alad->buddies;
		eb_account *tmp;

		while (node) {
			tmp = (eb_account *)node->data;
			if (strcmp(aim_normalize(tmp->handle),
					aim_normalize(handle)) == 0) {
				LOG(("Yeah this code is useful ! :)"))
					result = tmp;
				break;
			}
			node = node->next;
		}
	}

	if (result) {
		if (should_update && (strcmp(handle, result->handle) != 0)) {
			WARNING(("Updating contact list from %s to %s",
					result->handle, handle))
				strncpy(result->handle, handle,
				sizeof(result->handle) - 1);
			write_contact_list();
		}
	}

	if (result) {
		LOG(("oscar_find_account_with_ela(): %s => %s", handle,
				result->account_contact->nick))
	} else {
		LOG(("oscar_find_account_with_ela(): nothing found"))
	}

	return result;
}
