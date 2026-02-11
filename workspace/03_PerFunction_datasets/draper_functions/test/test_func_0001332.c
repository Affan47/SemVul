object_add_keyval (yajl_value_t *obj,
    yajl_value_t *key, yajl_value_t *value)
{
  yajl_value_object_t *o;
  yajl_value_t **tmp;

  if ((obj == NULL) || (key == NULL) || (value == NULL))
    return (EINVAL);

  if (!YAJL_IS_STRING (key))
    return (EINVAL);

  o = YAJL_TO_OBJECT (obj);
  if (o == NULL)
    return (EINVAL);

  tmp = realloc (o->keys, sizeof (*o->keys) * (o->children_num + 1));
  if (tmp == NULL)
    return (ENOMEM);
  o->keys = tmp;

  tmp = realloc (o->values, sizeof (*o->values) * (o->children_num + 1));
  if (tmp == NULL)
    return (ENOMEM);
  o->values = tmp;

  o->keys[o->children_num] = key;
  o->values[o->children_num] = value;
  o->children_num++;

  return (0);
}
