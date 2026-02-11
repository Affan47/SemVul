get_stringmap_value(stringmap *map, z_ucs *name)
{
  int result_index = get_stringmap_value_index(map, name);

  return result_index >= 0
    ? map->elements[result_index]->value
    : NULL;
}
