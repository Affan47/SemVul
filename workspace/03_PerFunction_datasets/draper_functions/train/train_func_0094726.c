stage_compare(const void *a, const void *b)
{
  const stage_plan *a_temp = *((const stage_plan * const *) a);
  const stage_plan *b_temp = *((const stage_plan * const *) b);

  if (a_temp->difficulty > b_temp->difficulty)
    return 1;
  else if (a_temp->difficulty < b_temp->difficulty)
    return -1;

  if ((a_temp->name != NULL) && (b_temp->name != NULL))
  {
    if (strcmp(a_temp->name, b_temp->name) != 0)
      return strcmp(a_temp->name, b_temp->name);
  }

  if (a_temp->stage_id > b_temp->stage_id)
    return 1;
  else if (a_temp->stage_id < b_temp->stage_id)
    return -1;

  return 0;
}
