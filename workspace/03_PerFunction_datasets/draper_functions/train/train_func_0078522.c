hm_vector_fwrite(const hm_vector_t *v, FILE *F){
	uint64_t be;

	const uint64_t start = ftello(F);


	hm_fileformat_line_t header;
	header.size = htobe64( (uint64_t) v->size );
	fwrite(& header, sizeof(header), 1, F);

	const uint64_t table_start = ftello(F);


	_hm_file_fwrite_junk(F, v->size);

	hm_listsize_t i;
	for(i = 0; i < v->size; i++){

		fseeko(F, 0, SEEK_END);
		const uint64_t abspos = ftello(F);

		hm_listdata_fwrite(v->buffer[i], F);


		fseeko(F, table_start + sizeof(uint64_t) * i, SEEK_SET);
		be = htobe64(abspos - start);
		fwrite(& be, sizeof(uint64_t), 1, F);
	}


	return 0;
}
