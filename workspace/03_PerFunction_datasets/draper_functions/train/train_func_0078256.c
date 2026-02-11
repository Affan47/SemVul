debug_record_typed_const (void *handle, const char *name, debug_type type,
			  bfd_vma val)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_name *n;
  struct debug_typed_constant *tc;

  if (name == NULL || type == NULL)
    return FALSE;

  n = debug_add_to_current_namespace (info, name, DEBUG_OBJECT_TYPED_CONSTANT,
				      DEBUG_LINKAGE_NONE);
  if (n == NULL)
    return FALSE;

  tc = (struct debug_typed_constant *) xmalloc (sizeof *tc);
  memset (tc, 0, sizeof *tc);

  tc->type = type;
  tc->val = val;

  n->u.typed_constant = tc;

  return TRUE;
}
