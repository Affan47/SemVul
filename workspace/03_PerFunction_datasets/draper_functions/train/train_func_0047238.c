MACE_tp_alloc(size_t n)
{
  char *return_block;
  int scale;


  scale = sizeof(void *);
  if (n % scale != 0)
    n = n + (scale - (n % scale));

  if (!Alloc_block || Alloc_block + TP_ALLOC_SIZE - Alloc_pos < n) {

    if (n > TP_ALLOC_SIZE)
      MACE_abend("in MACE_tp_alloc, request too big.");
    else if (MACE_Parms[MACE_MAX_MEM].val != -1 &&
	     ((Malloc_calls - Free_calls)+1)*(TP_ALLOC_SIZE/1024.0) >
	     MACE_Parms[MACE_MAX_MEM].val) {

      exit_with_message(MACE_MAX_MEM_EXIT, 1);
    }
    else {
      Alloc_pos = Alloc_block = (char *) malloc((size_t) TP_ALLOC_SIZE);
      if (!Alloc_pos)
	MACE_abend("in MACE_tp_alloc, operating system cannot supply any more memory.");
      Malloc_calls++;
      add_chunk(Alloc_block);
    }
  }
  return_block = Alloc_pos;
  Alloc_pos += n;
  return(return_block);
}
