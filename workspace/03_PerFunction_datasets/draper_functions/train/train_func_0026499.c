get_custom_block_run(blkid_probe pr,
				const struct befs_super_block *bs,
				const struct block_run *br,
				int64_t offset, uint32_t length, int fs_le)
{
	if (offset + length > (int64_t) FS16_TO_CPU(br->len, fs_le)
					<< FS32_TO_CPU(bs->block_shift, fs_le))
		return NULL;

	return blkid_probe_get_buffer(pr,
			((blkid_loff_t) FS32_TO_CPU(br->allocation_group, fs_le)
					<< FS32_TO_CPU(bs->ag_shift, fs_le)
					<< FS32_TO_CPU(bs->block_shift, fs_le))
				+ ((blkid_loff_t) FS16_TO_CPU(br->start, fs_le)
					<< FS32_TO_CPU(bs->block_shift, fs_le))
				+ offset,
			length);
}
