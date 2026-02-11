introspect (GType type,
            gint  indent)
{
  GType      *children;
  guint       count;
  gint        no;

  if (!type)
    return;

  fprintf (file, "<hr/>\n");
  fprintf (file, "<h3><a name='%s'>%s</a></h3>\n", g_type_name (type),
                                                   g_type_name (type));
  list_superclasses (type);
  details_for_type (type);
  list_subclasses (type);

  children=g_type_children (type, &count);

  if (!children)
    return;

  for (no=0; no<count; no++)
    {
      introspect (children[no], indent+2);
    }
  g_free (children);
}
