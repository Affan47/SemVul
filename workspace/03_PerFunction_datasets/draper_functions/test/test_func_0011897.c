is_boot_sector_ntfs(const struct super_block *sb,
		const NTFS_BOOT_SECTOR *b, const bool silent)
{


	if ((void*)b < (void*)&b->checksum && b->checksum && !silent) {
		le32 *u;
		u32 i;

		for (i = 0, u = (le32*)b; u < (le32*)(&b->checksum); ++u)
			i += le32_to_cpup(u);
		if (le32_to_cpu(b->checksum) != i)
			ntfs_warning(sb, "Invalid boot sector checksum.");
	}

	if (b->oem_id != magicNTFS)
		goto not_ntfs;

	if (le16_to_cpu(b->bpb.bytes_per_sector) < 0x100 ||
			le16_to_cpu(b->bpb.bytes_per_sector) > 0x1000)
		goto not_ntfs;

	switch (b->bpb.sectors_per_cluster) {
	case 1: case 2: case 4: case 8: case 16: case 32: case 64: case 128:
		break;
	default:
		goto not_ntfs;
	}

	if ((u32)le16_to_cpu(b->bpb.bytes_per_sector) *
			b->bpb.sectors_per_cluster > NTFS_MAX_CLUSTER_SIZE)
		goto not_ntfs;

	if (le16_to_cpu(b->bpb.reserved_sectors) ||
			le16_to_cpu(b->bpb.root_entries) ||
			le16_to_cpu(b->bpb.sectors) ||
			le16_to_cpu(b->bpb.sectors_per_fat) ||
			le32_to_cpu(b->bpb.large_sectors) || b->bpb.fats)
		goto not_ntfs;

	if ((u8)b->clusters_per_mft_record < 0xe1 ||
			(u8)b->clusters_per_mft_record > 0xf7)
		switch (b->clusters_per_mft_record) {
		case 1: case 2: case 4: case 8: case 16: case 32: case 64:
			break;
		default:
			goto not_ntfs;
		}

	if ((u8)b->clusters_per_index_record < 0xe1 ||
			(u8)b->clusters_per_index_record > 0xf7)
		switch (b->clusters_per_index_record) {
		case 1: case 2: case 4: case 8: case 16: case 32: case 64:
			break;
		default:
			goto not_ntfs;
		}


	if (!silent && b->end_of_sector_marker != cpu_to_le16(0xaa55))
		ntfs_warning(sb, "Invalid end of sector marker.");
	return true;
not_ntfs:
	return false;
}
