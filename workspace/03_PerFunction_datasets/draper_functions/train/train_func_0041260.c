hide_bubble(struct state *st, Bubble *bb)

{
  if (null_bubble(bb)) {
    fprintf(stderr, "NULL bubble passed to hide_bubble\n");
    exit(1);
  }

  if (bb->visible) {
    bb->visible = 0;

    if (st->simple) {
      XDrawArc(st->dpy, st->window, st->erase_gc, (bb->x - bb->radius),
	       (bb->y - bb->radius), bb->radius*2, bb->radius*2, 0,
	       360*64);
    } else {
#ifdef FANCY_BUBBLES
      if (! st->broken) {
	XSetClipOrigin(st->dpy, st->step_pixmaps[bb->step]->erase_gc,
		       (bb->x - bb->radius), (bb->y - bb->radius));

	XFillRectangle(st->dpy, st->window, st->step_pixmaps[bb->step]->erase_gc,
		       (bb->x - bb->radius),
		       (bb->y - bb->radius),
		       (bb->radius * 2),
		       (bb->radius * 2));
      }
#endif
    }
  }
}
