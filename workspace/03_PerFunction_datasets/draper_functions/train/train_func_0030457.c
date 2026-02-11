ntfs_mft_record_layout(const ntfs_volume *vol, const s64 mft_no,
		MFT_RECORD *m)
{
	ATTR_RECORD *a;

	ntfs_debug("Entering for mft record 0x%llx.", (long long)mft_no);
	if (mft_no >= (1ll << 32)) {
		ntfs_error(vol->sb, "Mft record number 0x%llx exceeds "
				"maximum of 2^32.", (long long)mft_no);
		return -ERANGE;
	}

	memset(m, 0, vol->mft_record_size);

	if (vol->major_ver < 3 || (vol->major_ver == 3 && !vol->minor_ver))
		m->usa_ofs = cpu_to_le16((sizeof(MFT_RECORD_OLD) + 1) & ~1);
	else {
		m->usa_ofs = cpu_to_le16((sizeof(MFT_RECORD) + 1) & ~1);


		m->reserved = 0;
		m->mft_record_number = cpu_to_le32((u32)mft_no);
	}
	m->magic = magic_FILE;
	if (vol->mft_record_size >= NTFS_BLOCK_SIZE)
		m->usa_count = cpu_to_le16(vol->mft_record_size /
				NTFS_BLOCK_SIZE + 1);
	else {
		m->usa_count = cpu_to_le16(1);
		ntfs_warning(vol->sb, "Sector size is bigger than mft record "
				"size.  Setting usa_count to 1.  If chkdsk "
				"reports this as corruption, please email "
				"linux-ntfs-dev@lists.sourceforge.net stating "
				"that you saw this message and that the "
				"modified filesystem created was corrupt.  "
				"Thank you.");
	}

	*(le16*)((u8*)m + le16_to_cpu(m->usa_ofs)) = cpu_to_le16(1);
	m->lsn = 0;
	m->sequence_number = cpu_to_le16(1);
	m->link_count = 0;


	m->attrs_offset = cpu_to_le16((le16_to_cpu(m->usa_ofs) +
			(le16_to_cpu(m->usa_count) << 1) + 7) & ~7);
	m->flags = 0;


	m->bytes_in_use = cpu_to_le32(le16_to_cpu(m->attrs_offset) + 8);
	m->bytes_allocated = cpu_to_le32(vol->mft_record_size);
	m->base_mft_record = 0;
	m->next_attr_instance = 0;

	a = (ATTR_RECORD*)((u8*)m + le16_to_cpu(m->attrs_offset));
	a->type = AT_END;
	a->length = 0;
	ntfs_debug("Done.");
	return 0;
}
