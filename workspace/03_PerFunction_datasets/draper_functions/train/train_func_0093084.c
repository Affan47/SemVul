locate_programmer_type(const char * id)
{
  const PROGRAMMER_TYPE * p = NULL;
  int i;
  int found;

  found = 0;

  for (i = 0; i < sizeof(programmers_types)/sizeof(programmers_types[0]) && !found; i++) {
    p = &(programmers_types[i]);
    if (strcasecmp(id, p->id) == 0)
        found = 1;
  }

  if (found)
    return p;

  return NULL;
}
