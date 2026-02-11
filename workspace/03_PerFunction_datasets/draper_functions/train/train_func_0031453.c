hash2header(const kh_ref_t *hash)
{
	bam_header_t *header;
	khiter_t k;
	header = bam_header_init();
	header->n_targets = kh_size(hash);
	header->target_name = (char**)calloc(kh_size(hash), sizeof(char*));
	header->target_len = (uint32_t*)calloc(kh_size(hash), 4);
	for (k = kh_begin(hash); k != kh_end(hash); ++k) {
		if (kh_exist(hash, k)) {
			int i = (int)kh_value(hash, k);
			header->target_name[i] = (char*)kh_key(hash, k);
			header->target_len[i] = kh_value(hash, k)>>32;
		}
	}
	bam_init_header_hash(header);
	return header;
}
