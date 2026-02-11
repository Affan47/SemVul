linear_search (unw_addr_space_t as, unw_word_t ip,
	       unw_word_t eh_frame_start, unw_word_t eh_frame_end,
	       unw_word_t fde_count,
	       unw_proc_info_t *pi, int need_unwind_info, void *arg)
{
  unw_accessors_t *a = unw_get_accessors (unw_local_addr_space);
  unw_word_t i = 0, fde_addr, addr = eh_frame_start;
  int ret;

  while (i++ < fde_count && addr < eh_frame_end)
    {
      fde_addr = addr;
      if ((ret = dwarf_extract_proc_info_from_fde (as, a, &addr, pi, 0, 0, arg))
	  < 0)
	return ret;

      if (ip >= pi->start_ip && ip < pi->end_ip)
	{
	  if (!need_unwind_info)
	    return 1;
	  addr = fde_addr;
	  if ((ret = dwarf_extract_proc_info_from_fde (as, a, &addr, pi,
						       need_unwind_info, 0,
						       arg))
	      < 0)
	    return ret;
	  return 1;
	}
    }
  return -UNW_ENOINFO;
}
