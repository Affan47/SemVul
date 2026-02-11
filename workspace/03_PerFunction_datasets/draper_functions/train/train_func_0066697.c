geoclue_address_details_get_accuracy_level (GHashTable *address)
{
	if (g_hash_table_lookup (address, GEOCLUE_ADDRESS_KEY_STREET)) {
		return GEOCLUE_ACCURACY_LEVEL_STREET;
	} else if (g_hash_table_lookup (address, GEOCLUE_ADDRESS_KEY_POSTALCODE)) {
		return GEOCLUE_ACCURACY_LEVEL_POSTALCODE;
	} else if (g_hash_table_lookup (address, GEOCLUE_ADDRESS_KEY_LOCALITY)) {
		return GEOCLUE_ACCURACY_LEVEL_LOCALITY;
	} else if (g_hash_table_lookup (address, GEOCLUE_ADDRESS_KEY_REGION)) {
		return GEOCLUE_ACCURACY_LEVEL_REGION;
	} else if (g_hash_table_lookup (address, GEOCLUE_ADDRESS_KEY_COUNTRY) ||
	           g_hash_table_lookup (address, GEOCLUE_ADDRESS_KEY_COUNTRYCODE)) {
		return GEOCLUE_ACCURACY_LEVEL_COUNTRY;
	}
	return GEOCLUE_ACCURACY_LEVEL_NONE;
}
