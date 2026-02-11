add_exclude (pattern)
     char const *pattern;
{
  if (exclude_alloc <= exclude_count)
    exclude = (char const **)
	      (exclude_alloc == 0
	       ? xmalloc ((exclude_alloc = 64) * sizeof (*exclude))
	       : xrealloc (exclude, (exclude_alloc *= 2) * sizeof (*exclude)));

  exclude[exclude_count++] = pattern;
}
