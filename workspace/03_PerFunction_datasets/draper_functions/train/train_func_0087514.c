read_chunk(chm_metadata_t *metadata)
{
	cli_dbgmsg("in read_chunk\n");

	if (metadata->itsp_hdr.block_len < 8 || metadata->itsp_hdr.block_len > 33554432) {
		return CL_EFORMAT;
	}

	if (metadata->chunk_offset > metadata->m_length) {
		return CL_EFORMAT;
	}
	if ((metadata->chunk_offset + metadata->itsp_hdr.block_len) > metadata->m_length) {
		return CL_EFORMAT;
	}
	metadata->chunk_data = fmap_need_off_once(metadata->map, metadata->chunk_offset, metadata->itsp_hdr.block_len);
	if(!metadata->chunk_data) return CL_EFORMAT;

	metadata->chunk_current = metadata->chunk_data + CHM_CHUNK_HDR_LEN;
	metadata->chunk_end = metadata->chunk_data + metadata->itsp_hdr.block_len;

	if (memcmp(metadata->chunk_data, "PMGL", 4) == 0) {
		metadata->chunk_entries = (uint16_t)((((uint8_t const *)(metadata->chunk_data))[metadata->itsp_hdr.block_len-2] << 0)
					| (((uint8_t const *)(metadata->chunk_data))[metadata->itsp_hdr.block_len-1] << 8));
	} else if (memcmp(metadata->chunk_data, "PMGI", 4) != 0) {
		return CL_BREAK;
	}

	return CL_SUCCESS;
}
