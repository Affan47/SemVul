PMI_Initialized( PMI_BOOL *initialized )
{
	if (pmi_debug)
		fprintf(stderr, "In: PMI_Initialized\n");

	if (initialized == NULL)
		return PMI_ERR_INVALID_ARG;

	if (pmi_init)
		*initialized = PMI_TRUE;
	else
		*initialized = PMI_FALSE;

	return PMI_SUCCESS;
}
