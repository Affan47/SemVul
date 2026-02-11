_erase_lines(struct state *st)
{
  if (!st->ii)
    return;
  for (st->di=st->bi; st->di<_min(st->eli+1,st->bi+st->elpu); st->di++) {
    if (st->eline[st->di].hv) {
      XFillRectangle (st->display, st->window, st->bgc,
      st->eline[st->di].x*st->elwid,
      st->eline[st->di].y*st->elwid,
      (st->eline[st->di].len+1)*st->elwid, st->elwid);
    } else {
      XFillRectangle (st->display, st->window, st->bgc,
      st->eline[st->di].x*st->elwid,
      st->eline[st->di].y*st->elwid,
      st->elwid, (st->eline[st->di].len+1)*st->elwid);
    }
    if (st->di==st->eli)
      XFillRectangle(st->display, st->window, st->bgc, 0, 0,
        st->xgwa.width, st->xgwa.height);
  }
  if (st->di>st->eli) {
      st->bi=1;
      if (st->resized) {
         st->mode=MODE_CREATE;
      } else {
         st->mode=MODE_DRAW;
      }
  } else {
      st->bi+=st->elpu;
  }
}
