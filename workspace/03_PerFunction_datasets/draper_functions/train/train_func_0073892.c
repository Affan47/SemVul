GC_register_dynlib_callback(info, size, ptr)
     struct dl_phdr_info * info;
     size_t size;
     void * ptr;
{
  const ElfW(Phdr) * p;
  char * start;
  register int i;


  if (size < offsetof (struct dl_phdr_info, dlpi_phnum)
      + sizeof (info->dlpi_phnum))
    return -1;

  p = info->dlpi_phdr;
  for( i = 0; i < (int)(info->dlpi_phnum); ((i++),(p++)) ) {
    switch( p->p_type ) {
      case PT_LOAD:
	{
	  if( !(p->p_flags & PF_W) ) break;
	  start = ((char *)(p->p_vaddr)) + info->dlpi_addr;
	  GC_add_roots_inner(start, start + p->p_memsz, TRUE);
	}
      break;
      default:
	break;
    }
  }

  * (int *)ptr = 1;
  return 0;
}
