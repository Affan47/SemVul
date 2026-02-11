get_src_info (bfd_vma addr, const char **filename, const char **name, int *line_num)
{
  const char *fname = 0, *func_name = 0;
  int l = 0;

  if (bfd_find_nearest_line (core_bfd, core_text_sect, core_syms,
			     addr - core_text_sect->vma,
			     &fname, &func_name, (unsigned int *) &l)
      && fname && func_name && l)
    {
      DBG (AOUTDEBUG, printf ("[get_src_info] 0x%lx -> %s:%d (%s)\n",
			      (unsigned long) addr, fname, l, func_name));
      *filename = fname;
      *name = func_name;
      *line_num = l;
      return TRUE;
    }
  else
    {
      DBG (AOUTDEBUG, printf ("[get_src_info] no info for 0x%lx (%s:%d,%s)\n",
			      (unsigned long) addr,
			      fname ? fname : "<unknown>", l,
			      func_name ? func_name : "<unknown>"));
      return FALSE;
    }
}
