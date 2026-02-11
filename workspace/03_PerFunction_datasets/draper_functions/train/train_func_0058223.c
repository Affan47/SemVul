dmalloc_error(const char *func)
{

  if (dmalloc_logpath != NULL
      || BIT_IS_SET(_dmalloc_flags, DEBUG_PRINT_MESSAGES)) {


    if (func == NULL) {
      func = "_malloc_error";
    }


    dmalloc_message("ERROR: %s: %s (err %d)",
		    func, dmalloc_strerror(dmalloc_errno), dmalloc_errno);
  }


  if (BIT_IS_SET(_dmalloc_flags, DEBUG_ERROR_ABORT)) {
    _dmalloc_die(0);
  }

#if HAVE_FORK

  if (BIT_IS_SET(_dmalloc_flags, DEBUG_ERROR_DUMP)) {
    if (fork() == 0) {
      _dmalloc_die(1);
    }
  }
#endif
}
