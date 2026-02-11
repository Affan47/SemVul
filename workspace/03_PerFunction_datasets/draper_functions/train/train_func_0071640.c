meta_builder_lookup_with_parent (MetaBuilder *builder,
				 const char *path,
				 gboolean create,
				 MetaFile **parent)
{
  MetaFile *f, *last;
  const char *element_start;
  char *element;

  last = NULL;
  f = builder->root;
  while (f)
    {
      while (*path == '/')
	path++;

      if (*path == 0)
	break;

      element_start = path;
      while (*path != 0 && *path != '/')
	path++;
      element = g_strndup (element_start, path - element_start);

      last = f;
      f = metafile_lookup_child (f, element, create);
      g_free (element);
    }

  if (parent)
    *parent = last;

  return f;
}
