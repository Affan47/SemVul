hm_linklist_fwrite(const hm_linklist_t *l, FILE *F){
	uint64_t be;

	const uint64_t start = ftello(F);


	hm_fileformat_line_t header;
	header.size = htobe64( (uint64_t) l->datacount );
	fwrite(& header, sizeof(header), 1, F);

	const uint64_t table_start = ftello(F);


	_hm_file_fwrite_junk(F, l->datacount);

	hm_listsize_t i = 0;
	const hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){

		fseeko(F, 0, SEEK_END);
		const uint64_t abspos = ftello(F);

		hm_listdata_fwrite(node->data, F);


		fseeko(F, table_start + sizeof(uint64_t) * i, SEEK_SET);
		be = htobe64(abspos - start);
		fwrite(& be, sizeof(uint64_t), 1, F);

		i++;
	}


	return 0;
}
