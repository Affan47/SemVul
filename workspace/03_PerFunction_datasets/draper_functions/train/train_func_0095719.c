stab_context (void)
{
  int i;

  fprintf (stderr, _("Last stabs entries before error:\n"));
  fprintf (stderr, "n_type n_desc n_value  string\n");

  i = saved_stabs_index;
  do
    {
      struct saved_stab *stabp;

      stabp = saved_stabs + i;
      if (stabp->string != NULL)
	{
	  const char *s;

	  s = bfd_get_stab_name (stabp->type);
	  if (s != NULL)
	    fprintf (stderr, "%-6s", s);
	  else if (stabp->type == 0)
	    fprintf (stderr, "HdrSym");
	  else
	    fprintf (stderr, "%-6d", stabp->type);
	  fprintf (stderr, " %-6d ", stabp->desc);
	  fprintf_vma (stderr, stabp->value);
	  if (stabp->type != 0)
	    fprintf (stderr, " %s", stabp->string);
	  fprintf (stderr, "\n");
	}
      i = (i + 1) % SAVE_STABS_COUNT;
    }
  while (i != saved_stabs_index);
}
