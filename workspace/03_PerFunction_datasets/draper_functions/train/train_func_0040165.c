_internal_removable_set_mps(int level, bitstr_t *bitmap,
					uint16_t *coords, bool mark,
					bool except)
{
	ba_mp_t *curr_mp;
	int is_set;

	if (level > cluster_dims)
		return;

	if (level < cluster_dims) {
		for (coords[level] = 0;
		     coords[level] < DIM_SIZE[level];
		     coords[level]++) {

			_internal_removable_set_mps(
				level+1, bitmap, coords, mark, except);
		}
		return;
	}

	slurm_mutex_lock(&ba_system_mutex);
	if (!(curr_mp = coord2ba_mp(coords))) {
		slurm_mutex_unlock(&ba_system_mutex);
		return;
	}
	if (bitmap)
		is_set = bit_test(bitmap, curr_mp->index);
	if (!bitmap || (is_set && !except) || (!is_set && except)) {
		if (mark) {
			if (ba_debug_flags & DEBUG_FLAG_BG_ALGO_DEEP)
				info("can't use %s", curr_mp->coord_str);
			curr_mp->used |= BA_MP_USED_TEMP;
			bit_set(ba_main_mp_bitmap, curr_mp->ba_geo_index);
		} else {
			curr_mp->used &= (~BA_MP_USED_TEMP);
			if (curr_mp->used == BA_MP_USED_FALSE)
				bit_clear(ba_main_mp_bitmap,
					  curr_mp->ba_geo_index);
		}
	}
	slurm_mutex_unlock(&ba_system_mutex);
}
