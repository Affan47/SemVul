tenm_table_add(tenm_object *object)
{
  int i;

  if (object == NULL)
  {
    fprintf(stderr, "tenm_table_add: object is NULL\n");
    return -1;
  }
  if ((object_table == NULL) || (action_needed == NULL))
  {
    fprintf(stderr, "tenm_table_add: table is not initialized\n");
    return -1;
  }

  for (i = 0; i < table_size; i++)
    if (object_table[i] == NULL)
    {
      object->table_index = i;
      object_table[i] = object;
      action_needed[i] = 0;
      return i;
    }
  fprintf(stderr, "tenm_table_add: no more space\n");
  return -1;
}
