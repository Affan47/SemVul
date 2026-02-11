ntfs_check_restart_area(struct inode *vi, RESTART_PAGE_HEADER *rp)
{
	u64 file_size;
	RESTART_AREA *ra;
	u16 ra_ofs, ra_len, ca_ofs;
	u8 fs_bits;

	ntfs_debug("Entering.");
	ra_ofs = le16_to_cpu(rp->restart_area_offset);
	ra = (RESTART_AREA*)((u8*)rp + ra_ofs);


	if (ra_ofs + offsetof(RESTART_AREA, file_size) >
			NTFS_BLOCK_SIZE - sizeof(u16)) {
		ntfs_error(vi->i_sb, "$LogFile restart area specifies "
				"inconsistent file offset.");
		return false;
	}


	ca_ofs = le16_to_cpu(ra->client_array_offset);
	if (((ca_ofs + 7) & ~7) != ca_ofs ||
			ra_ofs + ca_ofs > NTFS_BLOCK_SIZE - sizeof(u16)) {
		ntfs_error(vi->i_sb, "$LogFile restart area specifies "
				"inconsistent client array offset.");
		return false;
	}


	ra_len = ca_ofs + le16_to_cpu(ra->log_clients) *
			sizeof(LOG_CLIENT_RECORD);
	if (ra_ofs + ra_len > le32_to_cpu(rp->system_page_size) ||
			ra_ofs + le16_to_cpu(ra->restart_area_length) >
			le32_to_cpu(rp->system_page_size) ||
			ra_len > le16_to_cpu(ra->restart_area_length)) {
		ntfs_error(vi->i_sb, "$LogFile restart area is out of bounds "
				"of the system page size specified by the "
				"restart page header and/or the specified "
				"restart area length is inconsistent.");
		return false;
	}


	if ((ra->client_free_list != LOGFILE_NO_CLIENT &&
			le16_to_cpu(ra->client_free_list) >=
			le16_to_cpu(ra->log_clients)) ||
			(ra->client_in_use_list != LOGFILE_NO_CLIENT &&
			le16_to_cpu(ra->client_in_use_list) >=
			le16_to_cpu(ra->log_clients))) {
		ntfs_error(vi->i_sb, "$LogFile restart area specifies "
				"overflowing client free and/or in use lists.");
		return false;
	}


	file_size = (u64)sle64_to_cpu(ra->file_size);
	fs_bits = 0;
	while (file_size) {
		file_size >>= 1;
		fs_bits++;
	}
	if (le32_to_cpu(ra->seq_number_bits) != 67 - fs_bits) {
		ntfs_error(vi->i_sb, "$LogFile restart area specifies "
				"inconsistent sequence number bits.");
		return false;
	}

	if (((le16_to_cpu(ra->log_record_header_length) + 7) & ~7) !=
			le16_to_cpu(ra->log_record_header_length)) {
		ntfs_error(vi->i_sb, "$LogFile restart area specifies "
				"inconsistent log record header length.");
		return false;
	}

	if (((le16_to_cpu(ra->log_page_data_offset) + 7) & ~7) !=
			le16_to_cpu(ra->log_page_data_offset)) {
		ntfs_error(vi->i_sb, "$LogFile restart area specifies "
				"inconsistent log page data offset.");
		return false;
	}
	ntfs_debug("Done.");
	return true;
}
