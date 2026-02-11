sendpoint(struct state *st, double expo)
{
  double tmpexpo;

  if (st->maxcolor > MAXCOLOR)
    abort();

#if 0


  if (expo < st->minexp)
    expo = st->minexp;
  else if (expo > maxexp)
    expo = maxexp;
#endif

  st->point.x++;
  tmpexpo = (st->negative) ? expo : -1.0 * expo;
  if (tmpexpo > 0) {
    if (!mono_p) {
      st->sendpoint_index = (int)(tmpexpo*st->lowrange/st->maxexp);
      st->sendpoint_index = ((st->sendpoint_index % st->lowrange) +
                             st->startcolor);
    }
    else
      st->sendpoint_index = 0;
  }
  else {
    if (!mono_p) {
      st->sendpoint_index = (int)(tmpexpo*st->numfreecols/st->minexp);
      st->sendpoint_index = ((st->sendpoint_index % st->numfreecols)
                             + st->mincolindex);
    }
    else
      st->sendpoint_index = 1;
  }
  BufferPoint(st, st->sendpoint_index, st->point.x, st->point.y);
  if (st->save) {
    if (st->frame > MAXFRAMES)
      abort();
    st->exponents[st->frame][st->expind[st->frame]++] = expo;
  }
  if (st->point.x >= st->width) {
    st->point.y++;
    st->point.x = 0;
    if (st->save) {
      st->b += st->b_inc;
      st->a = st->min_a;
    }
    if (st->point.y >= st->height)
      return FALSE;
    else
      return TRUE;
  }
  return TRUE;
}
