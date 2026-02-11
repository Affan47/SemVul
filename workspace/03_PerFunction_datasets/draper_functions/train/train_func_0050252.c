smf_new(void)
{
	int cantfail;

	smf_t *smf = malloc(sizeof(smf_t));
	if (smf == NULL) {
		g_critical("Cannot allocate smf_t structure: %s", strerror(errno));
		return (NULL);
	}

	memset(smf, 0, sizeof(smf_t));

	smf->tracks_array = g_ptr_array_new();
	assert(smf->tracks_array);

	smf->tempo_array = g_ptr_array_new();
	assert(smf->tempo_array);

	cantfail = smf_set_ppqn(smf, 120);
	assert(!cantfail);

	cantfail = smf_set_format(smf, 0);
	assert(!cantfail);

	smf_init_tempo(smf);

	return (smf);
}
