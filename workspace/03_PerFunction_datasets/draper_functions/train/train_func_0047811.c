make_temp_string(glui32 addr)
{
  int ix, len;
  glui32 addr2;
  char *res;

  if (Mem1(addr) != 0xE0)
    fatal_error("String argument to a Glk call must be unencoded.");
  addr++;

  for (addr2=addr; Mem1(addr2); addr2++) { };
  len = (addr2 - addr);
  if (len < STATIC_TEMP_BUFSIZE) {
    res = temp_buf;
  }
  else {
    res = (char *)glulx_malloc(len+1);
    if (!res)
      fatal_error("Unable to allocate space for string argument to Glk call.");
  }

  for (ix=0, addr2=addr; ix<len; ix++, addr2++) {
    res[ix] = Mem1(addr2);
  }
  res[len] = '\0';

  return res;
}
