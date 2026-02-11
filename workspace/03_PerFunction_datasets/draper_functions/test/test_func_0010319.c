show_bubble(struct state *st, Bubble *bb)

{
  if (null_bubble(bb)) {
    fprintf(stderr, "NULL bubble passed to show_bubble\n");
    exit(1);
  }

  if (! bb->visible) {
    bb->visible = 1;

    if (st->simple) {
      XDrawArc(st->dpy, st->window, st->draw_gc, (bb->x - bb->radius),
	       (bb->y - bb->radius), bb->radius*2, bb->radius*2, 0,
	       360*64);
    } else {
#ifdef FANCY_BUBBLES
      XSetClipOrigin(st->dpy, st->step_pixmaps[bb->step]->draw_gc,
		     (bb->x - bb->radius),
		     (bb->y - bb->radius));

      XCopyArea(st->dpy, st->step_pixmaps[bb->step]->ball, st->window,
		st->step_pixmaps[bb->step]->draw_gc,
		0, 0, (bb->radius * 2),
		(bb->radius * 2),
		(bb->x - bb->radius),
		(bb->y - bb->radius));
#endif
    }
  }
}
