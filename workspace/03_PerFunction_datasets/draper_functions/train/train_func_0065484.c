next_position (struct position **next_ptr, struct position *base,
	       enum position_type type, int arg)
{
  struct position *pos;

  pos = *next_ptr;
  if (!pos)
    {
      pos = XCNEW (struct position);
      pos->base = base;
      pos->type = type;
      pos->arg = arg;
      pos->depth = base->depth + 1;
      *next_ptr = pos;
    }
  return pos;
}
