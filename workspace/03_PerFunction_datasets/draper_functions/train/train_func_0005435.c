brz_destroy_keys_vd(cmph_uint8 ** keys_vd, cmph_uint32 nkeys)
{
	cmph_uint8 i;
	for(i = 0; i < nkeys; i++) { free(keys_vd[i]); keys_vd[i] = NULL;}
}
