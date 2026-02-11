automap_set_connection(int location, int d, int dest, BOOL is_real)
{
  loc_node *r, *t;

  r = room_find_or_create(location, is_real);
  t = room_find_or_create(dest, is_real);

  if(t == r)
    t = NULL;

  r->exits[d] = t;
}
