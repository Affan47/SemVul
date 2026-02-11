ra_realloc(struct RDArgs *rdargs, UBYTE **start, UBYTE **end)
{
  UBYTE *oldstart=*start;
  ULONG newlength=((*end-oldstart+144)&~0x7f)-8;
  UBYTE *newstart=ra_alloc(rdargs, newlength+4);

  if(!newstart)
    return NULL;

  *start=newstart;
  *end=newstart+newlength;
  return oldstart;
}
