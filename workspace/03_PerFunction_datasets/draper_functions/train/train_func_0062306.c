__libc_dlsym (void *map, const char *name)
{
  struct do_dlsym_args args;
  args.map = map;
  args.name = name;

#ifdef SHARED
  if (__builtin_expect (_dl_open_hook != NULL, 0))
    return _dl_open_hook->dlsym (map, name);
#endif
  return (dlerror_run (do_dlsym, &args) ? NULL
	  : (void *) (DL_SYMBOL_ADDRESS (args.loadbase, args.ref)));
}
