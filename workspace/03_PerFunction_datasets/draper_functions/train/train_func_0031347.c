stack_redraw()
{
  Stack *s;

  for (s=stacks; s; s=s->next)
    stack_redraw_stack(s);
  if (nodrop_showing)
    put_picture(nodrop, nodrop_x, nodrop_y, 0, 0, nodrop->w, nodrop->h);
}
