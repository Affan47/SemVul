_hm_file_locate_bsearch(const char *mem, const char *key, uint64_t *ppos){
	const hm_fileformat_line_t *head = (hm_fileformat_line_t *) mem;

	uint64_t start = 0;
	uint64_t end = be64toh(head->size);

	while (start < end){
		uint64_t mid = start + ((end - start) >> 1);

		const uint64_t ptr = be64toh( head->data[mid] );
		const void *pair = & mem[ptr];


		const int cmp = strcmp(hm_listdata_getkey(pair), key);

		if (cmp == 0){
			if (ppos)
				*ppos = mid;

			return pair;
		}

		if (cmp < 0){

			start = mid + 1;
		}else{

			end = mid;
		}
	}

	return NULL;
}
