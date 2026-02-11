get_symbol(LIBRARY *lib, const char *symbol, bool err)
{
  void *sym;

  sym = lt_dlsym(lib->handle, symbol);
  if (sym == NULL && err)
  {
    strcpy(COMMON_buffer, lt_dlerror());
    lt_dlclose(lib->handle);
    lib->handle = NULL;
    THROW(E_LIBRARY, lib->name, COMMON_buffer);
  }

  return sym;
}
