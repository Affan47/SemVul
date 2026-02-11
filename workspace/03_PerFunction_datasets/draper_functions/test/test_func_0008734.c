clear_norms_table (unsigned level, const wfa_info_t *wi, motion_t *mt)


{
   unsigned  range_size = wi->half_pixel
			  ? square (wi->search_range)
			  : square (2 * wi->search_range);

   if (level > wi->p_min_level)
   {
      memset (mt->mc_forward_norms [level], 0, range_size * sizeof(real_t));
      memset (mt->mc_backward_norms [level], 0, range_size * sizeof(real_t));
   }
}
