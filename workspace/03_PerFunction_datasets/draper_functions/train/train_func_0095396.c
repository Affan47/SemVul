dump_enable_all (int flags)
{
  int ir_dump_type = (flags & (TDF_TREE | TDF_RTL | TDF_IPA));
  int n = 0;
  size_t i;

  for (i = TDI_none + 1; i < (size_t) TDI_end; i++)
    if ((dump_files[i].flags & ir_dump_type))
      {
        dump_files[i].state = -1;
        dump_files[i].flags |= flags;
        n++;
      }

  for (i = 0; i < extra_dump_files_in_use; i++)
    if ((extra_dump_files[i].flags & ir_dump_type))
      {
        extra_dump_files[i].state = -1;
        extra_dump_files[i].flags |= flags;
	n++;
      }

  return n;
}
