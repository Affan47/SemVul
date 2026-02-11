vink_tree_get_string_default (const struct vink_tree* t, const char* path, const char* def)
{
  size_t i;

  for(i = 0; i < t->node_count; ++i)
    {
      if(!strcmp(t->nodes[i].path, path))
        return t->nodes[i].value;
    }

  return def;
}
