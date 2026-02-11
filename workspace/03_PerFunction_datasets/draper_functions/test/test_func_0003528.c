stab_range_type (void *p, bfd_signed_vma low, bfd_signed_vma high)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  bfd_boolean definition;
  unsigned int size;
  char *s, *buf;

  definition = info->type_stack->definition;
  size = info->type_stack->size;

  s = stab_pop_type (info);
  buf = (char *) xmalloc (strlen (s) + 100);
  sprintf (buf, "r%s;%ld;%ld;", s, (long) low, (long) high);
  free (s);

  if (! stab_push_string (info, buf, 0, definition, size))
    return FALSE;

  free (buf);

  return TRUE;
}
