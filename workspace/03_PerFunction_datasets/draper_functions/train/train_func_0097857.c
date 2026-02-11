gegl_instrument (const gchar *parent_name,
                 const gchar *name,
                 long         usecs)
{
  Timing *iter;
  Timing *parent;

  if (root == NULL)
    {
      root       = g_slice_new0 (Timing);
      root->name = g_strdup (parent_name);
    }
  parent = timing_find (root, parent_name);
  if (!parent)
    {
      gegl_instrument (root->name, parent_name, 0);
      parent = timing_find (root, parent_name);
    }
  g_assert (parent);
  iter = timing_find (parent, name);
  if (!iter)
    {
      iter             = g_slice_new0 (Timing);
      iter->name       = g_strdup (name);
      iter->parent     = parent;
      iter->next       = parent->children;
      parent->children = iter;
    }
  iter->usecs += usecs;
}
