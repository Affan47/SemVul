cbf_realloc (void **old_block, size_t *old_nelem,
                 size_t elsize, size_t nelem)
{
  void *new_block;


  if (!old_block || elsize == 0)

    return CBF_ARGUMENT;


  if (old_nelem)

    if (*old_nelem == nelem)

      return 0;


  if (nelem > 0)
  {

#ifdef CBFLIB_MEM_DEBUG

    char * cnew_block;

#endif

    new_block = malloc (nelem * elsize + sizeof(size_t));

    if (!new_block)

      return CBF_ALLOC;

    *(size_t *)new_block = nelem * elsize;

#ifdef CBFLIB_MEM_DEBUG

    fprintf(stderr, "allocated %ld size %ld\n",(long)new_block,(long)(nelem * elsize));

    cnew_block = (char *)new_block;

    cnew_block += sizeof(size_t);

    new_block = (void *)cnew_block;

    memory_allocated += nelem * elsize;

#endif

  }
  else

    new_block = NULL;


  if (old_nelem)

    if (*old_block && *old_nelem > 0 && nelem > 0)
    {
      if (*old_nelem > nelem)

        *old_nelem = nelem;

      memcpy (new_block, *old_block, *old_nelem * elsize);
    }


  if (*old_block)  {

#ifdef CBFLIB_MEM_DEBUG

    char * cold_block;

    cold_block = (void *)(*old_block);

    (cold_block) -= sizeof(size_t);

    *old_block = (char *)cold_block;

    memory_allocated -= *(size_t *)(*old_block);

    fprintf(stderr, "freeing %ld size %ld\n",(long)(*old_block),(long)(*(size_t *)(*old_block)));

#endif

    free (*old_block);

  }


  if (!old_nelem)

    memset (new_block, 0, nelem * elsize);

  else

    if (nelem > 0 && nelem > *old_nelem)

      memset (((char *) new_block) + *old_nelem * elsize, 0,
                                     (nelem - *old_nelem) * elsize);


  *old_block = new_block;

  if (old_nelem)

    *old_nelem = nelem;


  return 0;
}
