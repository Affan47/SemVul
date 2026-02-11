___err_code_from_errno ___PVOID
#endif
{
  int e = errno;

#ifdef ___DEBUG
  ___printf ("*** OS ERROR AT \"%s\"@%d.1 -- errno=%d (%s)\n",
             file,
             lineno,
             e,
             errno_to_string (e));
#endif

  if (e == 0)
    return ___FIX(___UNKNOWN_ERR);

  return ___FIX(___ERRNO_ERR(e));
}
