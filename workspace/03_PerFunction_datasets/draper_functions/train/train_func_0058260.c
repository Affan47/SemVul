buf_LRU_drop_page_hash_batch(

	ulint		space_id,
	ulint		zip_size,

	const ulint*	arr,
	ulint		count)
{
	ulint	i;

	ut_ad(arr != NULL);
	ut_ad(count <= BUF_LRU_DROP_SEARCH_SIZE);

	for (i = 0; i < count; ++i) {
		btr_search_drop_page_hash_when_freed(space_id, zip_size,
						     arr[i]);
	}
}
