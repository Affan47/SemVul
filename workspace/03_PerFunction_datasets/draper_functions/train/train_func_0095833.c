Realloc(const char *caller, const char *file, int line, void *ptrold, size_t size)
{
  void *ptr = NULL;
  int item = UNDEFID;

  memInit();

  if ( size > 0 )
    {
      ptr = realloc(ptrold, size);

      if ( MEM_Debug )
	{
	  memAccess++;

	  if ( ptr )
	    {
	      item = memListChangeEntry(ptrold, ptr, size, caller, file, line);

	      if ( item == UNDEFID )
		item = memListNewEntry(REALLOC_FUNC, ptr, size, 1, caller, file, line);
	    }

	  memListPrintEntry(REALLOC_FUNC, item, size, ptr, caller, file, line);
	}

      if ( ptr == NULL && dmemory_ExitOnError )
	memError(caller, file, line, size);
    }
  else
    fprintf(stderr, "Warning (%s) : Allocation of 0 bytes! [ line %d file %s ]\n", caller, line, file);

  return (ptr);
}
