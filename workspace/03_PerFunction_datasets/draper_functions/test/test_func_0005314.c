bitmap_check(struct dm_block_validator *v,
			struct dm_block *b,
			size_t block_size)
{
	struct disk_bitmap_header *disk_header = dm_block_data(b);
	__le32 csum_disk;

	if (dm_block_location(b) != le64_to_cpu(disk_header->blocknr)) {
		DMERR_LIMIT("bitmap check failed: blocknr %llu != wanted %llu",
			    le64_to_cpu(disk_header->blocknr), dm_block_location(b));
		return -ENOTBLK;
	}

	csum_disk = cpu_to_le32(dm_bm_checksum(&disk_header->not_used,
					       block_size - sizeof(__le32),
					       BITMAP_CSUM_XOR));
	if (csum_disk != disk_header->csum) {
		DMERR_LIMIT("bitmap check failed: csum %u != wanted %u",
			    le32_to_cpu(csum_disk), le32_to_cpu(disk_header->csum));
		return -EILSEQ;
	}

	return 0;
}
