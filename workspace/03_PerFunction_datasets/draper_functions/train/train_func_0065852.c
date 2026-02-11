itsf_read_header(chm_metadata_t *metadata)
{
	chm_itsf_header_t *itsf_hdr = &metadata->itsf_hdr;
	if (!chm_read_data(metadata->map, (char *)itsf_hdr, 0, CHM_ITSF_MIN_LEN))
		return FALSE;
	if (memcmp(itsf_hdr->signature, "ITSF", 4) != 0) {
		cli_dbgmsg("ITSF signature mismatch\n");
		return FALSE;
	}
	itsf_hdr->version = chm_endian_convert_32(itsf_hdr->version);
	itsf_hdr->header_len = chm_endian_convert_32(itsf_hdr->header_len);
	itsf_hdr->last_modified = chm_endian_convert_32(itsf_hdr->last_modified);
	itsf_hdr->lang_id = chm_endian_convert_32(itsf_hdr->lang_id);
	itsf_hdr->sec0_offset = chm_endian_convert_64(itsf_hdr->sec0_offset);
	itsf_hdr->sec0_len = chm_endian_convert_64(itsf_hdr->sec0_len);
	itsf_hdr->dir_offset = chm_endian_convert_64(itsf_hdr->dir_offset);
	itsf_hdr->dir_len = chm_endian_convert_64(itsf_hdr->dir_len);
	if (itsf_hdr->version > 2) {
		itsf_hdr->data_offset = chm_endian_convert_64(itsf_hdr->data_offset);
	}
	return TRUE;
}
