hm_vector_put(hm_vector_t *v, hm_pair_t *newpair){
	const char *key = hm_pair_getkey(newpair);

	hm_vectorsize_t index;
	int cmp = _hm_vector_locate_position(v, key, & index);

	if (cmp == 0){


		hm_pair_t *pair = v->buffer[index];


		if (pair->created > newpair->created){

			free(newpair);
			return 0;
		}

		free(pair);
		v->buffer[index] = newpair;
		return 1;
	}

	if ( ! _hm_vector_shiftR(v, index) )
		return 0;


	v->buffer[index] = newpair;
	return 1;
}
