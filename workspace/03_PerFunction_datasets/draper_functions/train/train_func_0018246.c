xcbc_prf_create(pseudo_random_function_t algo)
{
	mac_t *xcbc;

	switch (algo)
	{
		case PRF_AES128_XCBC:
			xcbc = xcbc_create(ENCR_AES_CBC, 16);
			break;
		case PRF_CAMELLIA128_XCBC:
			xcbc = xcbc_create(ENCR_CAMELLIA_CBC, 16);
			break;
		default:
			return NULL;
	}
	if (xcbc)
	{
		return mac_prf_create(xcbc);
	}
	return NULL;
}
