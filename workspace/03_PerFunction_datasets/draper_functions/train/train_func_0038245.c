ath_regd_find_country_by_name(char *alpha2)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(allCountries); i++) {
		if (!memcmp(allCountries[i].isoName, alpha2, 2))
			return allCountries[i].countryCode;
	}

	return -1;
}
