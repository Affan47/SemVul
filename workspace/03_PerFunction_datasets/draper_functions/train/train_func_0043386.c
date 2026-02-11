temp_free(ptr)
char *ptr;
{
  int blocktype = TEMP_BLOCK;
  if ( memdebug )
  {
     sprintf(errmsg,"temp_free %p ",ptr);
     erroutstring(errmsg);
  }
  THREADBLOCK(blocktype);

  list_free(ptr,blocktype);

}
