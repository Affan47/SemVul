_enchant_broker_request_dict (EnchantBroker * broker, const char *const tag)
{
	EnchantDict * dict;
	GSList * list;
	GSList * listIter;

	dict = (EnchantDict*)g_hash_table_lookup (broker->dict_map, (gpointer) tag);
	if (dict) {
		((EnchantDictPrivateData*)dict->enchant_private_data)->reference_count++;
		return dict;
	}

	list = enchant_get_ordered_providers (broker, tag);
	for (listIter = list; listIter != NULL; listIter = g_slist_next (listIter))
		{
			EnchantProvider * provider;

			provider = (EnchantProvider *) listIter->data;

			if (provider->request_dict)
				{
					dict = (*provider->request_dict) (provider, tag);

					if (dict)
						{
							EnchantSession *session;
							EnchantDictPrivateData *enchant_dict_private_data;

							session = enchant_session_new (provider, tag);
							enchant_dict_private_data = g_new0 (EnchantDictPrivateData, 1);
							enchant_dict_private_data->reference_count = 1;
							enchant_dict_private_data->session = session;
							dict->enchant_private_data = (void *)enchant_dict_private_data;
							g_hash_table_insert (broker->dict_map, (gpointer)g_strdup (tag), dict);
							break;
						}
				}
		}

	g_slist_free (list);

	return dict;
}
