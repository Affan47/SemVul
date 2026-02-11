legacy_consumer_is_replicationdn(const char *dn)
{
	int return_value = 0;

	if (NULL != dn && '\0' != dn[0])
	{
		if (NULL != legacy_consumer_replicationdn)
        {
            Slapi_DN *sdn = slapi_sdn_new_dn_byref (dn);

			if (slapi_sdn_compare (legacy_consumer_replicationdn, sdn) == 0) {
				return_value = 1;
			}

            slapi_sdn_free (&sdn);
		}
	}
    return return_value;
}
