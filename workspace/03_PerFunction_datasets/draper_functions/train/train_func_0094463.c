wms_malloc(uint bufsize)  {
  void  *ret;

  if (bufsize == 0)
    return(NULL);
  ret = malloc(bufsize);
  assert(ret != NULL);
  if (ret == NULL)  {
    fprintf(stderr, "%s: FATAL ERROR: Failed to allocate %d bytes.\n",
	    wms_progname, bufsize);
    exit(1);
  }
  return(ret);
}
