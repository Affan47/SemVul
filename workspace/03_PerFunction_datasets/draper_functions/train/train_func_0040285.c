upper_size_to_lower_size(struct ecryptfs_crypt_stat *crypt_stat,
			 unsigned long upper_size)
{
	unsigned long lower_size;

	lower_size = ( crypt_stat->header_extent_size
		       * crypt_stat->num_header_extents_at_front );
	if (upper_size != 0) {
		unsigned long num_extents;

		num_extents = upper_size / crypt_stat->extent_size;
		if (upper_size % crypt_stat->extent_size)
			num_extents++;
		lower_size += (num_extents * crypt_stat->extent_size);
	}
	return lower_size;
}
