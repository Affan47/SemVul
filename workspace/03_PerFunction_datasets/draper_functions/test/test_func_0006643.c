__dladdr1 (const void *address, Dl_info *info, void **extra, int flags)
{
# ifdef SHARED
  if (__builtin_expect (_dlfcn_hook != NULL, 0))
    return _dlfcn_hook->dladdr1 (address, info, extra, flags);
# endif

  switch (flags)
    {
    default:
    case 0:
      return _dl_addr (address, info, NULL, NULL);
    case RTLD_DL_SYMENT:
      return _dl_addr (address, info, NULL, (const ElfW(Sym) **) extra);
    case RTLD_DL_LINKMAP:
      return _dl_addr (address, info, (struct link_map **) extra, NULL);
    }
}
