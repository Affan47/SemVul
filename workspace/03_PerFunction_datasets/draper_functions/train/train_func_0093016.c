libmpq__file_offset(mpq_archive_s *mpq_archive, uint32_t file_number, libmpq__off_t *offset) {


	CHECK_FILE_NUM(file_number, mpq_archive)


	*offset = mpq_archive->mpq_block[mpq_archive->mpq_map[file_number].block_table_indices].offset + (((long long)mpq_archive->mpq_block_ex[mpq_archive->mpq_map[file_number].block_table_indices].offset_high) << 32);


	return LIBMPQ_SUCCESS;
}
