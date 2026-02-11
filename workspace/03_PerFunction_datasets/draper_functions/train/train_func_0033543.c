dm_exception_store_set_chunk_size(struct dm_exception_store *store,
				      unsigned chunk_size,
				      char **error)
{

	if (!is_power_of_2(chunk_size)) {
		*error = "Chunk size is not a power of 2";
		return -EINVAL;
	}


	if (chunk_size %
	    (bdev_logical_block_size(dm_snap_cow(store->snap)->bdev) >> 9) ||
	    chunk_size %
	    (bdev_logical_block_size(dm_snap_origin(store->snap)->bdev) >> 9)) {
		*error = "Chunk size is not a multiple of device blocksize";
		return -EINVAL;
	}

	if (chunk_size > INT_MAX >> SECTOR_SHIFT) {
		*error = "Chunk size is too high";
		return -EINVAL;
	}

	store->chunk_size = chunk_size;
	store->chunk_mask = chunk_size - 1;
	store->chunk_shift = __ffs(chunk_size);

	return 0;
}
