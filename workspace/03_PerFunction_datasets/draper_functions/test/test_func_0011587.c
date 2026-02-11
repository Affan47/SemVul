hm_file_linegetat(const hm_file_t *mmf, uint64_t pos){
	const char *mem = mmf->mem;

	const hm_fileformat_line_t *head = (hm_fileformat_line_t *) mem;
	uint64_t end = be64toh(head->size);

	if (pos >= end)
		return NULL;

	const uint64_t ptr = be64toh( head->data[pos] );
	const void *pair = & mem[ptr];

	return pair;
}
