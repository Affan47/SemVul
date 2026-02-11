pr_struct_field (void *p, const char *name, bfd_vma bitpos, bfd_vma bitsize,
		 enum debug_visibility visibility)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char ab[20];
  char *t;

  if (! substitute_type (info, name))
    return FALSE;

  if (! append_type (info, "; /* "))
    return FALSE;

  if (bitsize != 0)
    {
      print_vma (bitsize, ab, TRUE, FALSE);
      if (! append_type (info, "bitsize ")
	  || ! append_type (info, ab)
	  || ! append_type (info, ", "))
	return FALSE;
    }

  print_vma (bitpos, ab, TRUE, FALSE);
  if (! append_type (info, "bitpos ")
      || ! append_type (info, ab)
      || ! append_type (info, " */\n")
      || ! indent_type (info))
    return FALSE;

  t = pop_type (info);
  if (t == NULL)
    return FALSE;

  if (! pr_fix_visibility (info, visibility))
    return FALSE;

  return append_type (info, t);
}
