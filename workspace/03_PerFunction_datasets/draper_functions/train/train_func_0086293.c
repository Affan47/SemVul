frob_extension (const char *s, const char *ext)
{
  const char *p;

  p = strrchr (lbasename (s), '.');
  if (! p)
    p = s + strlen (s);

  obstack_grow (&temporary_obstack, s, p - s);
  return (char *) obstack_copy0 (&temporary_obstack, ext, strlen (ext));
}
