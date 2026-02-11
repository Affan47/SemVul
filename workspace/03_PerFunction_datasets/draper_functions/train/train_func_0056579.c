test_extent_translation(void)
{
	struct ecryptfs_crypt_stat crypt_stat;
	unsigned long lower_page_idx;
	int byte_offset;
	int rc = 0;
	size_t i;

	printf("Testing ecryptfs_extent_to_lwr_pg_idx_and_offset()... ");
	crypt_stat.extent_size = ECRYPTFS_EXTENT_SIZE;
	for (i = 0;
	     i < (sizeof(translation_test_vector)
		  / sizeof(struct translation_test_vector_element));
	     i++) {
		crypt_stat.header_extent_size =
			translation_test_vector[i].header_extent_size;
		crypt_stat.num_header_extents_at_front =
		translation_test_vector[i].num_header_extents_at_front;
		ecryptfs_extent_to_lwr_pg_idx_and_offset(
			&lower_page_idx, &byte_offset, &crypt_stat,
			translation_test_vector[i].extent_num,
			translation_test_vector[i].page_size);
		if (lower_page_idx
		    != translation_test_vector[i].lower_page_idx) {
			rc = -1;
			printf("\nError on test vector entry [%zu]; "
			       "lower_page_idx = [%lu]\n", i, lower_page_idx);
			goto out;
		}
		if (byte_offset
		    != translation_test_vector[i].byte_offset) {
			rc = -1;
			printf("\nError on test vector entry [%zd]; "
			       "byte offset = [%d]\n", i, byte_offset);
			goto out;
		}
	}
out:
	if (!rc) {
		printf("Pass\n");
	}
	return rc;
}
