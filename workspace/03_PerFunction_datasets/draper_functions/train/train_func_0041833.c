nilfs_compute_checksum(struct the_nilfs *nilfs,
				  struct buffer_head *bhs, u32 *sum,
				  unsigned long offset, u64 check_bytes,
				  sector_t start, unsigned long nblock)
{
	unsigned int blocksize = nilfs->ns_blocksize;
	unsigned long size;
	u32 crc;

	BUG_ON(offset >= blocksize);
	check_bytes -= offset;
	size = min_t(u64, check_bytes, blocksize - offset);
	crc = crc32_le(nilfs->ns_crc_seed,
		       (unsigned char *)bhs->b_data + offset, size);
	if (--nblock > 0) {
		do {
			struct buffer_head *bh;

			bh = __bread(nilfs->ns_bdev, ++start, blocksize);
			if (!bh)
				return -EIO;
			check_bytes -= size;
			size = min_t(u64, check_bytes, blocksize);
			crc = crc32_le(crc, bh->b_data, size);
			brelse(bh);
		} while (--nblock > 0);
	}
	*sum = crc;
	return 0;
}
