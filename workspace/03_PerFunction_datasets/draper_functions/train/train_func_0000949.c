PMI_Get_clique_size( int *size )
{
	char *env;

	if (pmi_debug)
		fprintf(stderr, "In: PMI_Get_clique_size\n");

	if (size == NULL)
		return PMI_ERR_INVALID_ARG;
	if (pmi_init == 0)
		return PMI_FAIL;


	if ((pmi_jobid == 0) && (pmi_stepid == 0)) {
		*size = 1;
		return PMI_SUCCESS;
	}

	env = getenv("SLURM_GTIDS");
	if (env) {
		int i, tids=1;
		for (i=0; env[i]; i++) {
			if (env[i] == ',')
				tids++;
		}
		*size = tids;
		return PMI_SUCCESS;
	}
	return PMI_FAIL;
}
