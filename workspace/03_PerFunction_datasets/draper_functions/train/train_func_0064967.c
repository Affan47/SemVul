debug_make_object_type (void *handle, bfd_boolean structp, bfd_vma size,
			debug_field *fields, debug_baseclass *baseclasses,
			debug_method *methods, debug_type vptrbase,
			bfd_boolean ownvptr)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_type_s *t;
  struct debug_class_type *c;

  t = debug_make_type (info,
		       structp ? DEBUG_KIND_CLASS : DEBUG_KIND_UNION_CLASS,
		       size);
  if (t == NULL)
    return DEBUG_TYPE_NULL;

  c = (struct debug_class_type *) xmalloc (sizeof *c);
  memset (c, 0, sizeof *c);

  c->fields = fields;
  c->baseclasses = baseclasses;
  c->methods = methods;
  if (ownvptr)
    c->vptrbase = t;
  else
    c->vptrbase = vptrbase;

  t->u.kclass = c;

  return t;
}
