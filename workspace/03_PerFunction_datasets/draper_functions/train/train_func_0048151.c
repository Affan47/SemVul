define_sub (sym, args_body, filename, linenum)
     Node *sym;
     Cons *args_body;
     char *filename;
     unsigned int linenum;
{
  void *old_data;

  if (!strhash_put (ns_subs, sym->u.sym, strlen (sym->u.sym), args_body,
		    &old_data))
    {
      fprintf (stderr, _("%s: ouf of memory"), program);
      exit (1);
    }
  if (old_data && warning_level >= WARN_ALL)
    fprintf (stderr, _("%s:%d: warning: redefining subroutine `%s'\n"),
	     filename, linenum, sym->u.sym);
}
