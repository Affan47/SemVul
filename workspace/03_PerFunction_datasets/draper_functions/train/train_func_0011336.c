dir_memcpy(struct adfs_dir *dir, unsigned int offset, void *to, int len)
{
	struct super_block *sb = dir->sb;
	unsigned int buffer, partial, remainder;

	buffer = offset >> sb->s_blocksize_bits;
	offset &= sb->s_blocksize - 1;

	partial = sb->s_blocksize - offset;

	if (partial >= len)
		memcpy(to, dir->bh_fplus[buffer]->b_data + offset, len);
	else {
		char *c = (char *)to;

		remainder = len - partial;

		memcpy(c,
			dir->bh_fplus[buffer]->b_data + offset,
			partial);

		memcpy(c + partial,
			dir->bh_fplus[buffer + 1]->b_data,
			remainder);
	}
}
