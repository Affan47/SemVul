cont_write_begin(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned flags,
			struct page **pagep, void **fsdata,
			get_block_t *get_block, loff_t *bytes)
{
	struct inode *inode = mapping->host;
	unsigned int blocksize = i_blocksize(inode);
	unsigned int zerofrom;
	int err;

	err = cont_expand_zero(file, mapping, pos, bytes);
	if (err)
		return err;

	zerofrom = *bytes & ~PAGE_CACHE_MASK;
	if (pos+len > *bytes && zerofrom & (blocksize-1)) {
		*bytes |= (blocksize-1);
		(*bytes)++;
	}

	return block_write_begin(mapping, pos, len, flags, pagep, get_block);
}
