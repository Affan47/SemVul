yajl_object_free (yajl_value_t *v)
{
  yajl_value_object_t *o;
  size_t i;

  o = YAJL_TO_OBJECT (v);
  if (o == NULL)
    return;

  for (i = 0; i < o->children_num; i++)
  {
    yajl_tree_free (o->keys[i]);
    o->keys[i] = NULL;
    yajl_tree_free (o->values[i]);
    o->values[i] = NULL;
  }

  free (o->keys);
  free (o->values);
  free (v);
}
