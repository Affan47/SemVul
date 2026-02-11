copy_orn_list (struct Ornament * list)
{
  struct Ornament * orn = NULL, * new = NULL, * old = list;

  if (list == NULL)
    return NULL;

  while (old != NULL)
  {
    if (new == NULL)
    {
      new = g_new (struct Ornament, 1);
      orn = new;
    }
    else
    {
      orn->next = g_new (struct Ornament, 1);
      orn = orn->next;
    }

    *orn = *old;
    orn->next = NULL;

    old = old->next;
  }
  return new;
}
