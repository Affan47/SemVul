_fillgrid(struct state *st)
{
  unsigned int gridc, n, add;

  gridc=st->gridx*st->dline[st->li].y+st->dline[st->li].x;
  add = (st->dline[st->li].hv) ? 1 : st->gridx;
  for (n=0;  n<=st->dline[st->li].len; n++) {
    if (n)
      gridc+=add;
    if (!st->grid[gridc].line) {
      st->fi++;
      st->grid[gridc].line=st->li;
    }
    if (st->dline[st->li].hv) {
      if (n)
        st->grid[gridc].hr=st->li;
      if (n<st->dline[st->li].len)
        st->grid[gridc].hl=st->li;
    } else {
      if (n)
        st->grid[gridc].vd=st->li;
      if (n<st->dline[st->li].len)
        st->grid[gridc].vu=st->li;
    }
    if (st->fi>=st->gridn) {
      st->grid_full=True;
      return;
    }
  }
}
