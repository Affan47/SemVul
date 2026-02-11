timing_find (Timing      *root,
                            const gchar *name)
{
  Timing *iter = root;

  if (!iter)
    return NULL;

  while (iter)
    {
      if (!strcmp (iter->name, name))
        return iter;
      if (timing_depth (iter_next (iter)) <= timing_depth (root))
        return NULL;
      iter = iter_next (iter);
    }
  return NULL;
}
