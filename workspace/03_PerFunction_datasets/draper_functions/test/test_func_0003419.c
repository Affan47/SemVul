__dlinfo (void *handle, int request, void *arg DL_CALLER_DECL)
{
# ifdef SHARED
  if (__builtin_expect (_dlfcn_hook != NULL, 0))
    return _dlfcn_hook->dlinfo (handle, request, arg,
				DL_CALLER);
# endif

  struct dlinfo_args args = { (ElfW(Addr)) DL_CALLER,
			      handle, request, arg };
  return _dlerror_run (&dlinfo_doit, &args) ? -1 : 0;
}
