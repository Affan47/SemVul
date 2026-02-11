debug_write_linenos (struct debug_handle *info,
		     const struct debug_write_fns *fns, void *fhandle,
		     bfd_vma address)
{
  while (info->current_write_lineno != NULL)
    {
      struct debug_lineno *l;

      l = info->current_write_lineno;

      while (info->current_write_lineno_index < DEBUG_LINENO_COUNT)
	{
	  if (l->linenos[info->current_write_lineno_index]
	      == (unsigned long) -1)
	    break;

	  if (l->addrs[info->current_write_lineno_index] >= address)
	    return TRUE;

	  if (! (*fns->lineno) (fhandle, l->file->filename,
				l->linenos[info->current_write_lineno_index],
				l->addrs[info->current_write_lineno_index]))
	    return FALSE;

	  ++info->current_write_lineno_index;
	}

      info->current_write_lineno = l->next;
      info->current_write_lineno_index = 0;
    }

  return TRUE;
}
