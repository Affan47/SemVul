ocfs2_block_check_compute(void *data, size_t blocksize,
			       struct ocfs2_block_check *bc)
{
	u32 crc;
	u32 ecc;

	memset(bc, 0, sizeof(struct ocfs2_block_check));

	crc = crc32_le(~0, data, blocksize);
	ecc = ocfs2_hamming_encode_block(data, blocksize);


	BUG_ON(ecc > USHRT_MAX);

	bc->bc_crc32e = cpu_to_le32(crc);
	bc->bc_ecc = cpu_to_le16((u16)ecc);
}
