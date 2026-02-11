dynports_find(u_int16_t port)
{
  int i;

  for (i=0; i<current_ptr; i++)
    if (dynport_map[i].port == port)
      return dynport_map[i].f;

  return NULL;
}
