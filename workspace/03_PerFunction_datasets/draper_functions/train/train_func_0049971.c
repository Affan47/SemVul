prepare_file(chm_metadata_t *metadata)
{
	uint64_t name_len, section;

	while (metadata->chunk_entries != 0) {
		if (metadata->chunk_current >= metadata->chunk_end) {
			return CL_EFORMAT;
		}

		name_len = read_enc_int(&metadata->chunk_current, metadata->chunk_end);
		if (((metadata->chunk_current + name_len) >= metadata->chunk_end) ||
				((metadata->chunk_current + name_len) < metadata->chunk_data)) {
			cli_dbgmsg("Bad CHM name_len detected\n");
			return CL_EFORMAT;
		}
		metadata->chunk_current += name_len;
		section = read_enc_int(&metadata->chunk_current, metadata->chunk_end);
		metadata->file_offset = read_enc_int(&metadata->chunk_current, metadata->chunk_end);
		metadata->file_length = read_enc_int(&metadata->chunk_current, metadata->chunk_end);
		metadata->chunk_entries--;
		if (section == 1) {
			return CL_SUCCESS;
		}
	}

	return CL_BREAK;
}
