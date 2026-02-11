output_hierarchy (FILE  *fp,
		  GType  type,
		  guint   level)
{
  guint i;
  GType *children;
  guint n_children;

  if (!type)
    return;


  for (i = 0; i < level; i++)
    fprintf (fp, "  ");
  fprintf (fp, "%s", g_type_name (type));
  fprintf (fp, "\n");

  children = g_type_children (type, &n_children);

  qsort (&children[0], n_children, sizeof (GType), type_cmp);

  for (i=0; i < n_children; i++) {
    output_hierarchy (fp, children[i], level + 1);
  }

  g_free (children);
}
