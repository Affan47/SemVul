gegl_operations_build (GList *list, GType type)
{
  GeglOperationClass *klass;
  GType *ops;
  guint  children;
  gint   no;

  if (!type)
    return list;

  klass = g_type_class_ref (type);
  if (klass->name != NULL)
    list = g_list_prepend (list, klass);

  ops = g_type_children (type, &children);

  for (no=0; no<children; no++)
    {
      list = gegl_operations_build (list, ops[no]);
    }
  if (ops)
    g_free (ops);
  return list;
}
