objc_encoding_init (void)
{
  gcc_obstack_init (&util_obstack);
  util_firstobj = (char *) obstack_finish (&util_obstack);
}
