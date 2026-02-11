IconUp (TwmWindow *tmp_win)
{
    int		x, y;
    int		defx, defy;
    struct IconRegion *ir;


    if (tmp_win->wmhints && (tmp_win->wmhints->flags & IconPositionHint))
      return (0);

    if (tmp_win->icon_moved) {
	if (!XGetGeometry (dpy, tmp_win->icon->w, &JunkRoot, &defx, &defy,
			   &JunkWidth, &JunkHeight, &JunkBW, &JunkDepth))
	  return (1);

	x = defx + ((int) JunkWidth) / 2;
	y = defy + ((int) JunkHeight) / 2;

	for (ir = Scr->FirstRegion; ir; ir = ir->next) {
	    if (x >= ir->x && x < (ir->x + ir->w) &&
		y >= ir->y && y < (ir->y + ir->h))
	      break;
	}
	if (!ir) return (0);
    }

    defx = -100;
    defy = -100;
    PlaceIcon(tmp_win, defx, defy, &x, &y);
    if (x != defx || y != defy) {
	XMoveWindow (dpy, tmp_win->icon->w, x, y);
	tmp_win->icon_moved = FALSE;
    }
    MaybeAnimate = True;
    return (0);
}
