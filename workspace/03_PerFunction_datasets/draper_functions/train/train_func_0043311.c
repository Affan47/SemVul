xrealloc (p, n)
     char *p;
     unsigned n;
{
  if (p == 0)
    return (char *)xmalloc (n);
  if (n == 0)
    {
      free (p);
      return 0;
    }
  p = (char *)realloc (p, n);
  if (p == 0)
    {
      fprintf (stderr, "virtual memory exhausted");
      cleanup ();
      exit (2);
    }
  return p;
}
