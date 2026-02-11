luaI_growvector (void **block, unsigned long nelems, int size,
                       char *errormsg, unsigned long limit)
{
  if (nelems >= limit)
    lua_error(errormsg);
  nelems = (nelems == 0) ? 20 : nelems*2;
  if (nelems > limit)
    nelems = limit;
  *block = luaI_realloc(*block, nelems*size);
  return (int)nelems;
}
