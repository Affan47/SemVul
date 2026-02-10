square_expose(XEvent *event)

{
  int rv = 0;
  struct jester_data *jd = NULL;

  XFindContext(display, event->xexpose.window, jester_context,
	       (XPointer *)&jd);

  if(pieces[jd->coords.x][jd->coords.y] == EMPTY)
    goto DONE;

  draw_piece(pieces[jd->coords.x][jd->coords.y], event->xexpose.window);

 DONE:
  return(rv);
}
