new_body(struct state *st)
{
  Body *p = malloc(sizeof(Body));
  if (!p) abort();
  p->epicycles = new_circle_chain(st);
  p->current_color = 0;
  p->next = NULL;
  p->x = p->y = 0;
  p->old_x = p->old_y = 0;
  p->x_origin = p->y_origin = 0;


  assign_random_common_w(p->epicycles);
  return p;
}
