_dmtcp_get_libc_dlsym_addr()
{
  static dlsym_fnptr_t _libc_dlsym_fnptr = NULL;

  if (_libc_dlsym_fnptr == NULL) {
    long dlsym_offset = 0;
    if (getenv(ENV_VAR_DLSYM_OFFSET) == NULL) {
      fprintf(stderr,
              "%s:%d DMTCP Internal Error: Env var DMTCP_DLSYM_OFFSET not set.\n"
              "      Aborting.\n\n",
              __FILE__, __LINE__);
      abort();
    }

    dlsym_offset = (long) strtol(getenv(ENV_VAR_DLSYM_OFFSET), NULL, 10);
    _libc_dlsym_fnptr = (dlsym_fnptr_t)((char *)&LIBDL_BASE_FUNC + dlsym_offset);

#ifndef PTRACE


#endif
    unsetenv ( ENV_VAR_DLSYM_OFFSET );
  }

  return (void*) _libc_dlsym_fnptr;
}
