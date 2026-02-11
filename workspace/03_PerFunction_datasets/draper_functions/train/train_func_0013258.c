_Unwind_Resume (struct _Unwind_Exception *exc)
{
  if (__builtin_expect (libgcc_s_resume == NULL, 0))
    init ();
  libgcc_s_resume (exc);
}
