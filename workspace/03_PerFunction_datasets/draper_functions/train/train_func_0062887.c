set_pos(double p)
{
  if (invert)
    pos = -p;
  else
    pos = p;
  queue_draw();
}
