chm_config_set_hashfuncs(cmph_config_t *mph, CMPH_HASH *hashfuncs)
{
	chm_config_data_t *chm = (chm_config_data_t *)mph->data;
	CMPH_HASH *hashptr = hashfuncs;
	cmph_uint32 i = 0;
	while(*hashptr != CMPH_HASH_COUNT)
	{
		if (i >= 2) break;
		chm->hashfuncs[i] = *hashptr;
		++i, ++hashptr;
	}
}
