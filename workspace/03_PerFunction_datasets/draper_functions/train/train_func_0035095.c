segment_executable (struct elf_segment_map *seg)
{
  if (seg->p_flags_valid)
    return (seg->p_flags & PF_X) != 0;
  else
    {


      unsigned int i;
      for (i = 0; i < seg->count; ++i)
	if (seg->sections[i]->flags & SEC_CODE)
	  return TRUE;
    }
  return FALSE;
}
