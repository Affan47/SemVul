stack_hide_nodrop()
{
  if (nodrop_showing)
  {
    nodrop_showing = 0;
    invalidate(nodrop_x, nodrop_y, nodrop->w, nodrop->h);
  }
}
