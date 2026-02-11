validate_region_size(struct raid_set *rs, unsigned long region_size)
{
	unsigned long min_region_size = rs->ti->len / (1 << 21);

	if (!region_size) {


		if (min_region_size > (1 << 13)) {

			region_size = roundup_pow_of_two(min_region_size);
			DMINFO("Choosing default region size of %lu sectors",
			       region_size);
		} else {
			DMINFO("Choosing default region size of 4MiB");
			region_size = 1 << 13;
		}
	} else {


		if (region_size > rs->ti->len) {
			rs->ti->error = "Supplied region size is too large";
			return -EINVAL;
		}

		if (region_size < min_region_size) {
			DMERR("Supplied region_size (%lu sectors) below minimum (%lu)",
			      region_size, min_region_size);
			rs->ti->error = "Supplied region size is too small";
			return -EINVAL;
		}

		if (!is_power_of_2(region_size)) {
			rs->ti->error = "Region size is not a power of 2";
			return -EINVAL;
		}

		if (region_size < rs->md.chunk_sectors) {
			rs->ti->error = "Region size is smaller than the chunk size";
			return -EINVAL;
		}
	}


	rs->md.bitmap_info.chunksize = (region_size << 9);

	return 0;
}
