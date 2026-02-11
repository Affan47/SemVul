corr_huff(unpack_data_t *unpack_data, unsigned int *char_set,
			unsigned int *num_to_place)
{
	int i, j;

	for (i=7 ; i >= 0 ; i--) {
		for (j=0 ; j < 32 ; j++, char_set++) {
			*char_set = (*char_set & ~0xff) | i;
		}
	}
	memset(num_to_place, 0, sizeof(unpack_data->ntopl));
	for (i=6 ; i >= 0 ; i--) {
		num_to_place[i] = (7-i) * 32;
	}
}
