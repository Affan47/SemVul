vt_execwrap_init()
{
#if defined(EXECWRAP_EXEC_AND_FORK) && \
    defined(HAVE_DECL_ENVIRON) && HAVE_DECL_ENVIRON

  void* libc_handle = vt_libwrap_get_libc_handle();
  vt_libassert(libc_handle);
  execwrap_libc_environ = (char***)dlsym(libc_handle, "environ");
  vt_libassert(execwrap_libc_environ);
#endif
}
