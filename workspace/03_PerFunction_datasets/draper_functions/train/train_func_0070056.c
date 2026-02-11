ocfs2_calc_extent_defrag_len(u32 *alloc_size, u32 *len_defraged,
					 u32 threshold, int *skip)
{
	if ((*alloc_size + *len_defraged) < threshold) {


		*len_defraged += *alloc_size;
	} else if (*len_defraged == 0) {


		*skip = 1;
	} else {


		*alloc_size = threshold - *len_defraged;
		*len_defraged = 0;
	}
}
