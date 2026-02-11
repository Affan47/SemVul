stab_start_block (void *p, bfd_vma addr)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;


  if (info->so_offset != -1)
    {
      bfd_put_32 (info->abfd, addr, info->symbols + info->so_offset + 8);
      info->so_offset = -1;
    }

  if (info->fun_offset != -1)
    {
      bfd_put_32 (info->abfd, addr, info->symbols + info->fun_offset + 8);
      info->fun_offset = -1;
    }

  ++info->nesting;


  if (info->nesting == 1)
    {
      info->fnaddr = addr;
      return TRUE;
    }


  if (info->pending_lbrac != (bfd_vma) -1)
    {
      if (! stab_write_symbol (info, N_LBRAC, 0, info->pending_lbrac,
			       (const char *) NULL))
	return FALSE;
    }


  info->pending_lbrac = addr - info->fnaddr;

  return TRUE;
}
