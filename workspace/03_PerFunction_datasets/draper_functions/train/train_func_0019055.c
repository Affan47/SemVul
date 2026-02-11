enchant_broker_dict_exists (EnchantBroker * broker,
				const char * const tag)
{
	char * normalized_tag;
	int exists = 0;

	g_return_val_if_fail (broker, 0);
	g_return_val_if_fail (tag && strlen(tag), 0);

	enchant_broker_clear_error (broker);

	normalized_tag = enchant_normalize_dictionary_tag (tag);

	if(!enchant_is_valid_dictionary_tag(normalized_tag))
		{
			enchant_broker_set_error (broker, "invalid tag character found");
		}
	else if ((exists = _enchant_broker_dict_exists (broker, normalized_tag)) == 0)
		{
			char * iso_639_only_tag;

			iso_639_only_tag = enchant_iso_639_from_tag (normalized_tag);

			if (strcmp (normalized_tag, iso_639_only_tag) != 0)
				{
					exists = _enchant_broker_dict_exists (broker, iso_639_only_tag);
				}

			g_free (iso_639_only_tag);
		}

	g_free (normalized_tag);
	return exists;
}
